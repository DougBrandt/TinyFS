
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "libTinyFS.h"
#include "libDisk.h"
#include "singlyLinkedList.h"

/* function prototypes */
int mountFS();
int checkFSValid(int disk);
int formatFS(int disk);
int findFileByName(char *filename);
int unmountFS();
int createFile(char *filename);
int getFreeBlocks(int disk, int numBlocks);
int tfs_truncate(int FD);

/* global variables */
int diskFD = -1;
LinkedList *linkedList = NULL;
int currentFD = 1;

int tfs_openFile(char *name) {
   int inodeBlockIdx = -1;
   FileTableEntry *fte = NULL;

   // check params
   if (name == NULL) {
      return -1;
   }

   // check for zero length
   if (strnlen(name, MAX_FILENAME_LEN) == 0) {
      return -1;
   }

   // check the disk
   if (diskFD == -1) {
      if ((diskFD = mountFS()) == -1) {
         return -1;
      }

      // initialize the file description table (aka. linked list)
      if (linkedList == NULL) {
         if (InitLL(&linkedList, comparator) == -1) {
            return -1;
         }
      }
   }

   int i;
   for (i = 0; i < LLSize(linkedList); i++) {
      fte = LLGet(linkedList, i);
      if (fte == NULL) {
         return -1;
      }
      if (fte->fileName == NULL || name == NULL) {
         return -1;
      }
      if (strncmp(fte->fileName, name, MAX_FILENAME_LEN) == 0) {
         // this file is already open
         return -1;
      }
   }

   // check for the file
   if ((inodeBlockIdx = findFileByName(name)) == -1) { // error
      return -1;
   }
   else if (inodeBlockIdx == 0) { // file not found
      if ((inodeBlockIdx = createFile(name)) == -1) {
         return -1;
      }
   }

   // allocate file table entry
   if ((fte = (FileTableEntry *)calloc(1, sizeof(FileTableEntry))) == NULL) {
      perror("calloc failed");
      return -1;
   }

   // initialize file table entry
   fte->fd = currentFD++;
   fte->inodeIdx = inodeBlockIdx;
   fte->curByteOffset = 0;
   strncpy(fte->fileName, name, MAX_FILENAME_LEN);

   LLInsertTail(linkedList, fte);

   return fte->fd;
}

int tfs_closeFile(int FD) {
   int fdIndex = -1;

   // check params
   if (FD < 0) {
      return -1;
   }

   // check the disk
   if (diskFD == -1) {
      return -1;
   }

   // check the file is open
   // get the index of the fd in the "table" (aka linked list)
   if ((fdIndex = LLIndexOf(linkedList, FD)) == -1) {
      return -1;
   }

   // remove the fd from the "table" and free the data
   free(LLRemove(linkedList, fdIndex));

   // close the file description table (aka. linked list) if last file
   if (LLSize(linkedList) == 0) {
      DestroyLL(&linkedList);
      linkedList = NULL;
      if (unmountFS() == -1) {
         return -1;
      }
   }

   return 0;
}

int tfs_writeFile(int FD, char *buffer) {
   uint8_t inodeBlock[BLOCK_SIZE] = "";
   uint8_t block[BLOCK_SIZE] = "";
   FileTableEntry *ftePtr = NULL;
   INodeBlockHDR *inbh = NULL;
   BlockHDR *bh = NULL;
   int fdIndex = -1;
   int blockIdx = -1;
   uint32_t dataLength = -1;
   int numBlocksNeeded = -1;

   // check params
   if (FD < 0 || buffer == NULL) {
      return -1;
   }

   // check the disk
   if (diskFD == -1) {
      return -1;
   }

   // truncate old data
   if (tfs_truncate(FD) == -1) {
      return -1;
   }

   // get the index of the fd in the "table" (aka linked list)
   if ((fdIndex = LLIndexOf(linkedList, FD)) == -1) {
      return -1;
   }

   // get the metadata - need the inode index
   ftePtr = LLGet(linkedList, fdIndex);

   // get inode block
   if (readBlock(diskFD, ftePtr->inodeIdx, inodeBlock) == -1) {
      return -1;
   }

   inbh = (INodeBlockHDR *)inodeBlock;

   // calculate number of free blocks
   dataLength = strlen(buffer);
   numBlocksNeeded = (int)ceil((double)dataLength / BLOCK_DATA_SIZE);

   // get the free blocks
   if ((blockIdx = getFreeBlocks(diskFD, numBlocksNeeded)) == -1) {
      return -1;
   }

   // update the inode
   inbh->blockHdr.type = INODE;
   inbh->blockHdr.addressNext = blockIdx;
   inbh->totalFileSize = dataLength;

   // write the updated inode block
   if (writeBlock(diskFD, ftePtr->inodeIdx, inodeBlock) == -1) {
      return -1;
   }

   int i = 0;
   for (i = 0; i < numBlocksNeeded; i++) {
      // read the block
      if (readBlock(diskFD, blockIdx, block) == -1) {
         return -1;
      }
      bh = (BlockHDR *)block;

      // update the block
      bh->type = FILE_EXTENDS;
      bh->magicNum = BLOCK_MAGIC_NUM;
      strncpy((char *)(block+sizeof(BlockHDR)), &buffer[i * BLOCK_DATA_SIZE],
               BLOCK_DATA_SIZE);

      // write the block
      if (writeBlock(diskFD, blockIdx, block) == -1) {
         return -1;
      }

      // update blockIdx and offset
      blockIdx = bh->addressNext;
   }

   // set the file point to the start of the file
   ftePtr->curByteOffset = 0;

   return 0;
}

int tfs_deleteFile(int FD) {
   uint8_t block[BLOCK_SIZE] = "";
   uint8_t superBlock[BLOCK_SIZE] = "";
   int fdIndex = -1;
   FileTableEntry *ftePtr = NULL;
   BlockHDR *bh = NULL;
   SuperBlockHDR *sbh = NULL;
   int nextBlockIdx = -1;
   int lastBlockIdx = -1;
   int totalFreed = 0;

   // check params
   if (FD < 0) {
      return -1;
   }

   // check the disk
   if (diskFD == -1) {
      return -1;
   }

   // get the index of the fd in the "table" (aka linked list)
   if ((fdIndex = LLIndexOf(linkedList, FD)) == -1) {
      return -1;
   }

   // get the metadata - need the inode index
   if ((ftePtr = LLGet(linkedList, fdIndex)) == NULL) {
      return -1;
   }

   // loop over the blocks - freeing them
   nextBlockIdx = ftePtr->inodeIdx;
   while(nextBlockIdx != 0) {
      // get the block
      if (readBlock(diskFD, nextBlockIdx, block) == -1) {
         return -1;
      }
      bh = (BlockHDR *)block;

      // update the next
      lastBlockIdx = nextBlockIdx;
      nextBlockIdx = bh->addressNext;

      // update the block
      bh->type = FREE;
      memset(block+sizeof(BlockHDR), 0, BLOCK_DATA_SIZE);

      totalFreed++;

      // write the block
      if(writeBlock(diskFD, lastBlockIdx, block) == -1) {
         return -1;
      }
   }

   // get the superblock
   if (readBlock(diskFD, 0, superBlock) == -1) {
      return -1;
   }
   sbh = (SuperBlockHDR *)superBlock;

   // update the next pointer in the last freed block
   bh->addressNext = sbh->firstFreeBlock;

   // update superblock
   sbh->firstFreeBlock = ftePtr->inodeIdx;
   sbh->freeCount += totalFreed;

   // rewrite the last freed block
   if(writeBlock(diskFD, lastBlockIdx, block) == -1) {
      return -1;
   }

   // write the super block
   if (writeBlock(diskFD, 0, superBlock) == -1) {
      return -1;
   }

   // close file descriptor
   return tfs_closeFile(FD);
}

int tfs_readByte(int FD, char *buffer) {
   uint8_t block[BLOCK_SIZE] = "";
   FileTableEntry *ftePtr = NULL;
   BlockHDR *bh = NULL;
   INodeBlockHDR *inbh = NULL;
   int fdIndex = -1;
   int targetNumBlocks = -1;
   int curNumBlocks = 0;
   int blockIdx = -1;

   // check params
   if (FD < 0) {
      return -1;
   }

   // check the disk
   if (diskFD == -1) {
      return -1;
   }

   // get the index of the fd in the "table" (aka linked list)
   if ((fdIndex = LLIndexOf(linkedList, FD)) == -1) {
      return -1;
   }

   // get the metadata - need the inode index
   ftePtr = LLGet(linkedList, fdIndex);

   // calculate the target number of blocks to move
   targetNumBlocks = (int)ceil((double)(ftePtr->curByteOffset + 1) / BLOCK_DATA_SIZE);

   // get the inode for the file
   if (readBlock(diskFD, ftePtr->inodeIdx, block) == -1) {
      return -1;
   }

   inbh = (INodeBlockHDR *)block;

   // ensure not reading past end of file
   if ((ftePtr->curByteOffset) >= (inbh->totalFileSize)) {
      buffer[0] = '\0';
      return -1;
   }

   // get the first data block
   blockIdx = inbh->blockHdr.addressNext;

   // move to the correct block
   do {

      // get the current block
      if (readBlock(diskFD, blockIdx, block) == -1) {
         return -1;
      }

      bh = (BlockHDR *)block;

      // update block index
      blockIdx = bh->addressNext;

      curNumBlocks++;
   } while (curNumBlocks < targetNumBlocks);

   // set the byte from the offset
   buffer[0] = block[sizeof(BlockHDR) +
                      (ftePtr->curByteOffset % BLOCK_DATA_SIZE)];

   // update file pointer (if not at end)
   if (buffer[0] != '\0') {
      (ftePtr->curByteOffset)++;
   }

   return 0;
}

int tfs_seek(int FD, int offset) {
   int fdIndex = -1;
   FileTableEntry *ftePtr = NULL;

   // check params
   if (FD < 0 || offset < 0) {
      return -1;
   }

   // check the disk
   if (diskFD == -1) {
      return -1;
   }

   // get the index of the fd in the "table" (aka linked list)
   if ((fdIndex = LLIndexOf(linkedList, FD)) == -1) {
      return -1;
   }

   // get the metadata - need the inode index
   ftePtr = LLGet(linkedList, fdIndex);

   // update the file table entry
   ftePtr->curByteOffset = offset;

   return 0;
}

int tfs_rename(int FD, char *filename) {
   uint8_t block[BLOCK_SIZE] = "";
   FileTableEntry *ftePtr = NULL;
   INodeBlockHDR *inbh = NULL;
   int fdIndex = -1;

   // check params
   if (FD < 0 || filename == NULL) {
      return -1;
   }

   // check the disk
   if (diskFD == -1) {
      return -1;
   }

   // get the index of the fd in the "table" (aka linked list)
   if ((fdIndex = LLIndexOf(linkedList, FD)) == -1) {
      return -1;
   }

   // get the metadata - need the inode index
   ftePtr = LLGet(linkedList, fdIndex);

   // get the inode for the file
   if (readBlock(diskFD, ftePtr->inodeIdx, block) == -1) {
      return -1;
   }
   inbh = (INodeBlockHDR *)block;

   // rename file
   strncpy(inbh->filename, filename, MAX_FILENAME_LEN);

   // write the inode with the update
   if (writeBlock(diskFD, ftePtr->inodeIdx, block) == -1) {
      return -1;
   }

   return 0;
}

int tfs_dir() {
   uint8_t block[BLOCK_SIZE] = "";
   BlockHDR *bh = NULL;
   INodeBlockHDR *ibh = NULL;
   char filename[MAX_FILENAME_LEN + 1] = "";
   int mountFlag = 0;

   // check the disk
   if (diskFD == -1) {
      if((diskFD = mountFS()) == -1) {
         return -1;
      }
      mountFlag = 1;
   }

   // loop through the entire disk, checking all inodes for our file name
   int i = 0;
   for (i = 1; readBlock(diskFD, i, block) == 0; i++) {
      // check the type of the block
      bh = (BlockHDR *)block;
      if (bh->type != INODE) {
         continue;
      }

      // if it is an inode, check the file name
      ibh = (INodeBlockHDR *)block;
      memset(filename, 0, MAX_FILENAME_LEN + 1);
      strncpy(filename, ibh->filename, MAX_FILENAME_LEN);
      printf("  %s\n", filename);
   }

   // restore disk to previous state
   if (mountFlag == 1) {
      unmountFS();
   }

   return 0;
}

time_t tfs_readFileInfo(int FD) {
   uint8_t block[BLOCK_SIZE] = "";
   FileTableEntry *ftePtr = NULL;
   INodeBlockHDR *inbh = NULL;
   int fdIndex = -1;

   // check params
   if (FD < 0) {
      return -1;
   }

   // check the disk
   if (diskFD == -1) {
      return -1;
   }

   // get the index of the fd in the "table" (aka linked list)
   if ((fdIndex = LLIndexOf(linkedList, FD)) == -1) {
      return -1;
   }

   // get the metadata - need the inode index
   ftePtr = LLGet(linkedList, fdIndex);

   // get the inode for the file
   if (readBlock(diskFD, ftePtr->inodeIdx, block) == -1) {
      return -1;
   }
   inbh = (INodeBlockHDR *)block;

   return inbh->creationTime;
}

int tfs_truncate(int FD) {
   uint8_t block[BLOCK_SIZE] = "";
   uint8_t superBlock[BLOCK_SIZE] = "";
   int fdIndex = -1;
   FileTableEntry *ftePtr = NULL;
   BlockHDR *bh = NULL;
   SuperBlockHDR *sbh = NULL;
   INodeBlockHDR *inbh = NULL;
   int nextBlockIdx = -1;
   int lastBlockIdx = -1;
   int totalFreed = 0;
   int firstFreedBlock = -1;

   // check the disk
   if (diskFD == -1) {
      return -1;
   }

   // check the is open
   // get the index of the fd in the "table" (aka linked list)
   if ((fdIndex = LLIndexOf(linkedList, FD)) == -1) {
      return -1;
   }

   // get the metadata - need the inode index
   ftePtr = LLGet(linkedList, fdIndex);

   // get the inode block
   if (readBlock(diskFD, ftePtr->inodeIdx, block) == -1) {
      return -1;
   }
   inbh = (INodeBlockHDR *)block;

   // get the first data block
   nextBlockIdx = inbh->blockHdr.addressNext;

   // if there is no data -> done
   if (nextBlockIdx == 0) {
      return 0;
   }
   else {
      firstFreedBlock = nextBlockIdx;
   }

   // update the inode
   inbh->totalFileSize = 0;
   inbh->blockHdr.addressNext = 0;

   // write the updated inode block
   if(writeBlock(diskFD, ftePtr->inodeIdx, block) == -1) {
      return -1;
   }

   // loop over the data blocks - freeing them
   while (nextBlockIdx != 0) {
      // get the data block
      if (readBlock(diskFD, nextBlockIdx, block) == -1) {
         return -1;
      }
      bh = (BlockHDR *)block;

      // update the next block to free
      lastBlockIdx = nextBlockIdx;
      nextBlockIdx = bh->addressNext;

      // update the block
      bh->type = FREE;
      memset(block+sizeof(BlockHDR), 0, BLOCK_DATA_SIZE);

      totalFreed++;

      // write the block
      if(writeBlock(diskFD, lastBlockIdx, block) == -1) {
         return -1;
      }
   }

   // get the superblock
   if (readBlock(diskFD, 0, superBlock) == -1) {
      return -1;
   }
   sbh = (SuperBlockHDR *)superBlock;

   // update the next pointer in the last freed block
   bh->addressNext = sbh->firstFreeBlock;

   // update superblock
   sbh->firstFreeBlock = firstFreedBlock;
   sbh->freeCount += totalFreed;

   // rewrite the last freed block
   if(writeBlock(diskFD, lastBlockIdx, block) == -1) {
      return -1;
   }

   // write the super block
   if (writeBlock(diskFD, 0, superBlock) == -1) {
      return -1;
   }

   return 0;
}

/*
 * open the disk (create it if necessary) and format it (if necessary)
 *
 * Return: -1 on error, disk# on success
 */
int mountFS() {
   int diskNum = -1;
   int isFSValid = -1;

   // check for the disk or create one
   if (isDiskExtant(DISK_NAME) == 1) {
      // open the disk
      if ((diskNum = openDisk(DISK_NAME, 0)) == -1) {
         return -1;
      }
   }
   else {
      // create the disk and open it
      if ((diskNum = openDisk(DISK_NAME, DISK_SIZE)) == -1) {
         return -1;
      }
   }

   // check FS exists
   if ((isFSValid = checkFSValid(diskNum)) == -1) {
      return -1;
   }
   else if (isFSValid == 0) {
      formatFS(diskNum);
   }

   return diskNum;
}

/*
 * Check if the disk is formatted/valid by checking the superblock.
 *
 * Returns: -1 on error, 0 on invalid, 1 on valid
 */
int checkFSValid(int disk) {
   uint8_t block[BLOCK_SIZE] = "";
   SuperBlockHDR *sbh = NULL;

   // get super block (block 0)
   if (readBlock(disk, 0, block) == -1) {
      return -1;
   }

   // cast to superblock and check magic number and other metadata
   sbh = (SuperBlockHDR *)block;

   if (sbh->blockHdr.type == SUPERBLOCK &&
       sbh->blockHdr.magicNum == BLOCK_MAGIC_NUM) {
      return 1;
   }

   return 0;
}

int formatFS(int disk) {
   uint8_t block[BLOCK_SIZE] = "";
   SuperBlockHDR *sbh = (SuperBlockHDR *)block;
   BlockHDR *bh = (BlockHDR *)block;
   int diskSize = -1;

   // package super block
   sbh->blockHdr.type = SUPERBLOCK;
   sbh->blockHdr.magicNum = BLOCK_MAGIC_NUM;
   if ((diskSize = getDiskSize(disk)) == -1) {
      return -1;
   }
   sbh->freeCount = ((diskSize / BLOCK_SIZE) - 1);
   sbh->firstFreeBlock = 1;

   if (writeBlock(disk, 0, block) == -1) {
      return -1;
   }

   // clean up
   sbh->freeCount = 0;
   sbh->firstFreeBlock = 0;

   // loop through the entire disk
   int i = 0;
   for (i = 1; ((diskSize / BLOCK_SIZE) - 1); i++) {

      // package free block
      bh->type = FREE;
      bh->magicNum = BLOCK_MAGIC_NUM;
      bh->addressNext = (i + 1);
      memset(block+sizeof(BlockHDR), 0, BLOCK_DATA_SIZE);

      // write free block
      if (writeBlock(disk, i, block) == -1) {
         return -1;
      }
   }

   // end free chain by pointing to superblock
   bh->addressNext = 0;
   if (writeBlock(disk, (i-1), block) == -1) {
      return -1;
   }

   return 0;
}

/*
 * Locate a file on the disk by a dumb search.
 *
 * Returns: block number of the file's inode, 0 if not found, or -1 on error
 */
int findFileByName(char *filename) {
   uint8_t block[BLOCK_SIZE] = "";
   BlockHDR *bh = NULL;
   INodeBlockHDR *ibh = NULL;

   // check params
   if (filename == NULL) {
      return -1;
   }

   // check the file system
   if (checkFSValid(diskFD) != 1) {
      return -1;
   }

   // loop through the entire disk, checking all inodes for our file name
   int i = 0;
   for (i = 1; readBlock(diskFD, i, block) == 0; i++) {
      // check the type of the block
      bh = (BlockHDR *)block;
      if (bh->type != INODE) {
         continue;
      }

      // if it is an inode, check the file name
      ibh = (INodeBlockHDR *)block;
      if (ibh == NULL || ibh->filename == NULL) {
         continue;
      }
      if (strncmp(filename, ibh->filename, MAX_FILENAME_LEN) == 0) {
         //if the name matched, we are done
         return i;
      }
   }

   //file not found
   return 0;
}

/*
 * unmountFS() closes the disk
 *
 * Return: -1 on error, 0 on success
 */
int unmountFS() {
   if (closeDisk(diskFD) == -1) {
      return -1;
   }

   // set disk to closed
   diskFD = -1;

   return 0;
}

/*
 * createFile() creates a inode for the new file
 *
 * Returns: -1 on error, 0 on success
 */
int createFile(char *filename) {
   uint8_t block[BLOCK_SIZE] = "";
   INodeBlockHDR *inbh = NULL;
   SuperBlockHDR *sbh = NULL;
   int blockIdx = -1;

   // check params
   if (filename == NULL) {
      return -1;
   }

   // check disk
   if (diskFD == -1) {
      return -1;
   }

   // get superblock
   if (readBlock(diskFD, 0, block) == -1) {
      return -1;
   }

   sbh = (SuperBlockHDR *)block;

   // check number of free blocks (must be greater than 2 in order to hold the
   //    inode and at least 1 block of data)
   if (sbh->freeCount < 2) {
      return -1;
   }

   // clean up
   memset(block, 0, BLOCK_SIZE); 

   // get a free block
   if ((blockIdx = getFreeBlocks(diskFD, 1)) == -1) {
      return -1;
   }

   inbh = (INodeBlockHDR *)block;

   // package the inode data
   inbh->blockHdr.type = INODE;
   inbh->blockHdr.magicNum = BLOCK_MAGIC_NUM;
   inbh->blockHdr.addressNext = 0;
   if (strncpy(inbh->filename, filename, MAX_FILENAME_LEN) == NULL) {
      return -1;
   }
   inbh->creationTime = time(NULL);
   inbh->totalFileSize = 0;

   // write the inode data
   if (writeBlock(diskFD, blockIdx, block) == -1) {
      return -1;
   }

   return blockIdx;
}

int getFreeBlocks(int disk, int numBlocks) {
   uint8_t superBlock[BLOCK_SIZE] = "";
   uint8_t freeBlock[BLOCK_SIZE] = "";
   SuperBlockHDR *sbh = NULL;
   BlockHDR *bh = NULL;
   int blockCount = 0;
   int firstFreeBlockIdx = -1;
   int curFreeBlockIdx = -1;
   int nextFreeBlockIdx = -1;

   // check params
   if (disk < 0 || numBlocks < 0) {
      return -1;
   }

   // get superblock
   if (readBlock(disk, 0, superBlock) == -1) {
      return -1;
   }

   sbh = (SuperBlockHDR *)superBlock;

   // check number of free blocks (must be >= numBlocks)
   if (sbh->freeCount < numBlocks) {
      return -1;
   }

   // get the first available free block
   nextFreeBlockIdx = sbh->firstFreeBlock;

   // save starting free block chain index
   firstFreeBlockIdx = nextFreeBlockIdx;

   do {
      // get the block
      if (readBlock(disk, nextFreeBlockIdx, freeBlock) == -1) {
         return -1;
      }

      bh = (BlockHDR *)freeBlock;

      curFreeBlockIdx = nextFreeBlockIdx;
      nextFreeBlockIdx = bh->addressNext;

      blockCount++;
   } while (blockCount < numBlocks);

   // update superblock with new next free block and counter
   sbh->freeCount -= numBlocks;
   sbh->firstFreeBlock = nextFreeBlockIdx;

   // update last free block to point to superblock
   bh->addressNext = 0;

   // write the super block
   if (writeBlock(disk, 0, superBlock) == -1) {
      return -1;
   }

   // write the last block in the chain
   if (writeBlock(disk, curFreeBlockIdx, freeBlock) == -1) {
      return -1;
   }

   return firstFreeBlockIdx;
}
