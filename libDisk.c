
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "libTinyFS.h"
#include "libDisk.h"


int openDisk(char *filename, int nBytes) {
   int fd = -1;
   int i = 0;

   // check params
   if (filename == NULL || nBytes < 0) {
      return -1;
   }

   if (nBytes == 0) {   // open already created file system
      if ((fd = open(filename, O_RDWR)) == -1) {
         return -1;
      }
   }
   else {               // open a "new" file system
      if ((fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR |
                               S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1) {
         return -1;
      }

      // write empty data to the file
      for (i = 0; i < nBytes; i++) {
         if (write(fd, "\0", 1) == -1) {
            return -1;
         }
      }
   }

   return fd;
}

int readBlock(int disk, int bNum, void *block) {
   int diskSize = -1;

   // check params
   if (disk < 0 || bNum < 0 || block == NULL) {
      return -1;
   }

   // get the disk size
   if ((diskSize = getDiskSize(disk)) == -1) {
      return -1;
   }

   // check that bNum is valid
   if (((bNum * BLOCK_SIZE) + BLOCK_SIZE) > diskSize) {
      return -1;
   }

   // seek to the correct location
   if (lseek(disk, bNum * BLOCK_SIZE, SEEK_SET) != (bNum * BLOCK_SIZE)) {
      return -1;
   }

   // read a block
   if (read(disk, block, BLOCK_SIZE) == -1) {
      return -1;
   }

   return 0;
}

int writeBlock(int disk, int bNum, void *block) {
   int diskSize = -1;

   // check params
   if (disk < 0 || bNum < 0 || block == NULL) {
      return -1;
   }

   // get the disk size
   if ((diskSize = getDiskSize(disk)) == -1) {
      return -1;
   }

   // check that bNum is valid
   if (((bNum * BLOCK_SIZE) + BLOCK_SIZE) > diskSize) {
      return -1;
   }

   // seek to the correct location
   if (lseek(disk, bNum * BLOCK_SIZE, SEEK_SET) != (bNum * BLOCK_SIZE)) {
      return -1;
   }

   // write a block
   if (write(disk, block, BLOCK_SIZE) == -1) {
      return -1;
   }

   return 0;
}

int closeDisk(int disk) {

   // check params
   if (disk < 0) {
      return -1;
   }

   // close the disk
   if (close(disk) == -1) {
      return -1;
   }

   return 0;
}

int isDiskExtant(char *filename) {
   int fd = -1;

   if ((fd = open(filename, O_RDWR)) == -1) {
      if (errno == EACCES) {
         // doesn't exist
         return 0;
      }
      return -1;
   }

   if (close(fd) == -1) {
      return -1;
   }

   // exists
   return 1;
}

int getDiskSize(int disk) {
   int diskSize = -1;

   // check params
   if (disk < 0) {
      return -1;
   }

   // get size
   if ((diskSize = lseek(disk, 0, SEEK_END)) == -1) {
      return -1;
   }

   return diskSize;
}

