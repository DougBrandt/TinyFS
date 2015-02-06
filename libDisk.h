
#ifndef __LIB_DISK_H_
#define __LIB_DISK_H_

#define DISK_NAME "tinyFSDisk"
#define DISK_SIZE 10240

/*
 * This functions opens a regular Unix file and designates the first nBytes of
 * it as space for the TinyFS Disk. If nBytes > 0 and there is already a file
 * by that name, that file's content will be overwritten. There is no
 * requirement to maintain integrity of any file content beyond nBytes. That
 * means, you can always open a new file and write nBytes to it. To open an
 * existing disk (assuming the filename is valid), call openDisk() with
 * nBytes = 0. The return value is -1 on failure or a disk# on success.
 */
int openDisk(char *filename, int nBytes);

/*
 * readBlock() reads an entire block of blockSize size from the open disk
 * (identified by the disk#) and copies the result into a local buffer (must be
 * at least of blockSize). The bNum is a block number, which must be translated
 * into a byte offset to be seek()ed in the Unix file. That translation is
 * simple: bNum=0 is the very first byte of the file. bNum=1 is blockSize
 * offset from the beginning of the file. bNum=X is X*blockSize bytes into the
 * file. On success, it returns 0. -1 or smaller is returned if Disk is not
 * available (hasn't been opened) or any other failures. You may define
 * your own error code system.
 */
int readBlock(int disk, int bNum, void *block);

/*
 * writeBlock() takes a disk# and a block number and writes the content of the
 * argument block to that location. Just as readBlock(), it must seek() to the
 * correct position in the file and then write to it. On success, it returns 0.
 * -1 or smaller is returned if Disk is not available (hasn't been opened)
 *  or any other failures. You may define your own error code system.
 */
int writeBlock(int disk, int bNum, void *block);

/*
 * closeDisk() takes a disk# and closes that associated disk.
 *
 * Return: -1 on error, 0 on success
 */
int closeDisk(int disk);

/*
 * Check to see if the disk exists
 *
 * return -1 on error, 0 on does not exist, 1 on exists
 */
int isDiskExtant(char *filename);

/*
 * Get the current size of the disk in bytes
 *
 * Return: -1 on error, size on success
 */
int getDiskSize(int disk);

#endif // __LIBDISK_H_

