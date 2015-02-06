
#ifndef __LIB_TINY_FS_H_
#define __LIB_TINY_FS_H_

#include <stdint.h>
#include <time.h>

// Block Size in Bytes
#define BLOCK_SIZE         256
#define MAX_FILENAME_LEN   8
#define BLOCK_MAGIC_NUM    45
// see #define BLOCK_DATA_SIZE below

// we don't use this, but the test program needed this 
typedef int fileDescriptor;

typedef enum {
   SUPERBLOCK = 1,
   INODE = 2,
   FILE_EXTENDS = 3,
   FREE = 4,
} BlockCodes;

struct block_hdr {
   uint8_t type;
   uint8_t magicNum;
   uint8_t addressNext;
   uint8_t empty;
} __attribute__((__packed__));

typedef struct block_hdr BlockHDR;

#define BLOCK_DATA_SIZE    (BLOCK_SIZE - sizeof(BlockHDR))

struct super_block_hdr {
   struct block_hdr blockHdr;
   uint32_t freeCount;
   uint32_t firstFreeBlock;
} __attribute__((__packed__));

typedef struct super_block_hdr SuperBlockHDR;

struct inode_block_hdr {
   struct block_hdr blockHdr;
   char filename[MAX_FILENAME_LEN];
   uint32_t totalFileSize;
   time_t creationTime;
} __attribute__((__packed__));

typedef struct inode_block_hdr INodeBlockHDR;

typedef struct {
   int fd;
   int inodeIdx;
   int curByteOffset;   // absolute byte offset from start of file
   char fileName[MAX_FILENAME_LEN];
} FileTableEntry;


/*
 * Opens a file for reading or writing. Create a dynamic resource table entry
 * for the file, and returns a file descriptor (integer) that can be used to
 * reference this file from now on.
 */
int tfs_openFile(char *name);

/*
 * Closes the file, de-allocates all system resources, and removes table entry
 */
int tfs_closeFile(int FD);

/*
 * writes an entire buffer, representing the entire file content, to a file.
 * Sets the file pointer to 0 (the very beginning) when done. Returns
 * success/error codes.
 */
int tfs_writeFile(int FD, char *buffer);

/*
 * deletes a file and marks its blocks available on disk.
 */
int tfs_deleteFile(int FD);

/*
 * reads one byte from the file and copies it to buffer, uses the current file
 * pointer location, and increments it by one after
 */
int tfs_readByte(int FD, char *buffer);

/*
 * change the file pointer location to offset (absolute)
 */
int tfs_seek(int FD, int offset);

/*
 * renames a file. New name should be passed in
 */
int tfs_rename(int FD, char *filename);

/*
 * list the files on the disk
 */
int tfs_dir();

/*
 * get the files creation time
 *
 * Note: A unix time stamp is returned to the user.
 *
 * Upon successfull completion, it shall return the value of time.  Otherwise,
 * (time_t)-1 shall be returned.
 */
time_t tfs_readFileInfo(int FD);


#endif // __LIB_TINY_FS_H_

