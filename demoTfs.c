
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libTinyFS.h"

int main(int argc, char *argv[]) {

   int fd = -1;
   int longFD = -1;
   int i = 0;

   int countTest = 0;

   char *tbuf1 = "This is a short string. There is not much in it.";
   char *longStr = "Steven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of Windows";

   char *tooBigStr = "Steven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of WindowsSteven Sinofsky became the president of the Windows division in July 2009. His first heavily-involved projects included Windows Live Wave 3 and Internet Explorer 8. Sinofsky and Jon DeVaan also headed the development of the next major version of Windows to come after Windows Vista, Windows 7. Sinofsky's philosophy on Windows 7 was to not make any promises about the product or even discuss anything about the product until Microsoft was sure that it felt like a quality product. This was a radical departure from Microsoft's typical way of handling in-development versions of Windows, which was to publicly share all plans and details about it early in the development cycle. Sinofsky also refrained from labeling versions of Windows";

/**************
 *
 * Test: Open new file, write small amount of data and close it
 *
 **************/

   countTest = 0;

   printf("Test 1: Open new file, write small amount of data and close it\n");

   // open file
   if ((fd = tfs_openFile("myfile00")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   // write some bytes
   if (tfs_writeFile(fd, tbuf1) == -1) {
      puts("tfs_write failed");
      exit(-1);
   }
   countTest++;

   // close the file
   if (tfs_closeFile(fd) == -1) {
      printf("tfs_closeFile failed\n");
      exit(-1);
   }
   countTest++;

   if (countTest == 3)
      printf("Test 1: Passed\n");
   else
      printf("Test 1: Failed\n");

/**************
 *
 * Test: Open file, delete file and try/fail to close it
 *
 **************/

   countTest = 0;

   printf("Test 2: Open file, delete file and try/fail to close it\n");

   //open the file again
   if ((fd = tfs_openFile("myfile00")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   //delete the file
   if (tfs_deleteFile(fd) == -1) {
      puts("tfs_delete failed");
      exit(-1);
   }
   countTest++;

   // close the file
   if (tfs_closeFile(fd) == -1) {
      //"this should fail since it was closed in delete"
      countTest++;
   }

   if (countTest == 3)
      printf("Test 2: Passed\n");
   else
      printf("Test 2: Failed\n");

/**************
 *
 * Test: Open new file, write file, read file and close it
 *
 **************/

   countTest = 0;

   printf("Test 3: Open new file, write file, read file and close it\n");

   //open the file again
   if ((fd = tfs_openFile("myfile00")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   //write some bytes
   if (tfs_writeFile(fd, tbuf1) == -1) {
      puts("tfs_write failed");
      exit(-1);
   }
   countTest++;

   // read the file
   char fileResult1[100] = "";
   i = 0;
   while(tfs_readByte(fd, &(fileResult1[i])) != -1) {
      if (fileResult1[i] == '\0') {
         break;
      }
      i++;
   }

   if (strcmp(fileResult1, tbuf1) == 0) {
      //printf("File Contents:\n[%s]\n", fileResult1);
      countTest++;
   }

   // close the file
   if (tfs_closeFile(fd) == -1) {
      printf("tfs_closeFile failed\n");
      exit(-1);
   }
   countTest++;

   if (countTest == 4)
      printf("Test 3: Passed\n");
   else
      printf("Test 3: Failed\n");

/**************
 *
 * Test: Open file, read file and close it
 *
 **************/

   countTest = 0;

   printf("Test 4: Open file, read file and close it\n");

   //open the file again
   if ((fd = tfs_openFile("myfile00")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   // reading to the end of the file
   char fileResult2[100] = "";
   i = 0;
   while(tfs_readByte(fd, &(fileResult2[i])) != -1) {
      if (fileResult2[i] == '\0') {
         break;
      }
      i++;
   }
   if (strcmp(fileResult2, tbuf1) == 0) {
      //printf("File Contents:\n[%s]\n", fileResult1);
      countTest++;
   }

   // close the file
   if (tfs_closeFile(fd) == -1) {
      printf("tfs_closeFile failed\n");
      exit(-1);
   }
   countTest++;

   if (countTest == 3)
      printf("Test 4: Passed\n");
   else
      printf("Test 4: Failed\n");

/**************
 *
 * Test: Open file, seek 10 bytes into the file, read file and close it
 *
 **************/

   countTest = 0;

   printf("Test 5: Open file, seek 10 bytes into the file, read file and close it\n");

   //open the file again
   if ((fd = tfs_openFile("myfile00")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   // seek into the file
   if (tfs_seek(fd, 10) == -1) {
      printf("tfs_seek failed\n");
      exit(-1);
   }
   countTest++;

   // read to end of the file
   char fileResult3[100] = "";
   i = 0;
   while(tfs_readByte(fd, &(fileResult3[i])) != -1) {
      if (fileResult3[i] == '\0') {
         break;
      }
      i++;
   }
   if (strcmp(fileResult3, tbuf1+10) == 0) {
      //printf("File Contents:\n[%s]\n", fileResult1);
      countTest++;
   }

   // close the file
   if (tfs_closeFile(fd) == -1) {
      printf("tfs_closeFile failed\n");
      exit(-1);
   }
   countTest++;

   if (countTest == 4)
      printf("Test 5: Passed\n");
   else
      printf("Test 5: Failed\n");

/**************
 *
 * Test: Open file, seek beyond the end of the file, read file and close it
 *
 **************/

   countTest = 0;

   printf("Test 6: Open file, seek beyond the end of the file, read file and close it\n");

   //open the file again
   if ((fd = tfs_openFile("myfile00")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   // seek past the end of the file
   if (tfs_seek(fd, 100) == -1) {
      printf("tfs_seek failed\n");
      exit(-1);
   }
   countTest++;

   // read to end of the file
   char fileResult4[100] = "";
   i = 0;
   while(tfs_readByte(fd, &(fileResult4[i])) != -1) {
      if (fileResult4[i] == '\0') {
         break;
      }
      i++;
   }
   if (strcmp(fileResult4, "") == 0) {
      //printf("File Contents:\n[%s]\n", fileResult1);
      countTest++;
   }

   // close the file
   if (tfs_closeFile(fd) == -1) {
      printf("tfs_closeFile failed\n");
      exit(-1);
   }
   countTest++;

   if (countTest == 4)
      printf("Test 6: Passed\n");
   else
      printf("Test 6: Failed\n");


/**************
 *
 * Test: Open new file, write multi-block file, read multi-block file and close it
 *
 **************/

   countTest = 0;

   printf("Test 7: Open new file, write multi-block file, read multi-block file and close it\n");

   // open file
   if ((longFD = tfs_openFile("myfile01")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   // write some bytes
   if (tfs_writeFile(longFD, longStr) == -1) {
      puts("tfs_write failed");
      exit(-1);
   }
   countTest++;

   // read the whole file
   char fileResult5[1000] = "";
   i = 0;
   while(tfs_readByte(longFD, &(fileResult5[i])) != -1) {
      if (fileResult5[i] == '\0') {
         break;
      }
      i++;
   }
   if (strcmp(fileResult5, longStr) == 0) {
      //printf("File Contents:\n[%s]\n", fileResult5);
      //printf(" vs   longStr:\n[%s]\n", longStr);
      countTest++;
   }

   // close the file
   if (tfs_closeFile(longFD) == -1) {
      printf("tfs_closeFile failed\n");
      exit(-1);
   }
   countTest++;

   if (countTest == 4)
      printf("Test 7: Passed\n");
   else
      printf("Test 7: Failed\n");


/**************
 *
 * Test: Open new multi-block file, write multi-block file that's too big, fail
 *          on write and close the file.
 *
 **************/

   countTest = 0;

   printf("Test 8: Open new multi-block file, write multi-block file that's too big, fail on write and close the file.pen new file, write multi-block file, read multi-block file and close it\n");

   int long2FD = -1;
   if ((long2FD = tfs_openFile("myfile02")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   //write some bytes
   if (tfs_writeFile(long2FD, tooBigStr) == -1) {
      //"This should fail since it is too big for the fs."
      countTest++;
   }

   // close the file
   if (tfs_closeFile(long2FD) == -1) {
      printf("tfs_closeFile failed\n");
      exit(-1);
   }
   countTest++;

   if (countTest == 3)
      printf("Test 8: Passed\n");
   else
      printf("Test 8: Failed\n");

/**************
 *
 * Test: Open 2 files at the same time, read from both and then close both.
 *
 **************/

   countTest = 0;

   printf("Test 9: Open 2 files at the same time, read from both and then close both.\n");

   // open file
   if ((fd = tfs_openFile("myfile00")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   // open file
   if ((longFD = tfs_openFile("myfile01")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   // read the first shorter file
   char fileResult9[100] = "";
   i = 0;
   while(tfs_readByte(fd, &(fileResult9[i])) != -1) {
      if (fileResult9[i] == '\0') {
         break;
      }
      i++;
   }
   if (strcmp(fileResult9, tbuf1) == 0) {
      //printf("File Contents:\n[%s]\n", fileResult1);
      countTest++;
   }

   // read the whole second longer (multi block) file
   char fileResult9_1[1000] = "";
   i = 0;
   while(tfs_readByte(longFD, &(fileResult9_1[i])) != -1) {
      if (fileResult9_1[i] == '\0') {
         break;
      }
      i++;
   }
   if (strcmp(fileResult9_1, longStr) == 0) {
      //printf("File Contents:\n[%s]\n", fileResult9_1);
      //printf(" vs   longStr:\n[%s]\n", longStr);
      countTest++;
   }

   // close the file
   if (tfs_closeFile(fd) == -1) {
      printf("tfs_closeFile fd failed\n");
      exit(-1);
   }
   countTest++;

   // close the file
   if (tfs_closeFile(longFD) == -1) {
      printf("tfs_closeFile longFD failed\n");
      exit(-1);
   }
   countTest++;

   if (countTest == 6)
      printf("Test 9: Passed\n");
   else
      printf("Test 9: Failed\n");

/**************
 *
 * Test: Try to open the same file twice. The second open will fail due to mandatory locking.
 *
 **************/

   countTest = 0;

   printf("Test 10: Try to open the same file twice. The second open will fail due to mandatory locking.\n");

   // open file
   if ((fd = tfs_openFile("myfile00")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   // open file
   if ((longFD = tfs_openFile("myfile00")) == -1) {
      //printf("tfs_openFile failed\n");
      countTest++;
   }

   // read the file
   char fileResult10[100] = "";
   i = 0;
   while(tfs_readByte(fd, &(fileResult10[i])) != -1) {
      if (fileResult10[i] == '\0') {
         break;
      }
      i++;
   }
   if (strcmp(fileResult10, tbuf1) == 0) {
      //printf("File Contents:\n[%s]\n", fileResult10);
      countTest++;
   }

   // close the file
   if (tfs_closeFile(fd) == -1) {
      printf("tfs_closeFile fd failed\n");
      exit(-1);
   }
   countTest++;

   // close the file
   if (tfs_closeFile(longFD) == -1) {
      //printf("tfs_closeFile longFD failed\n");
      countTest++;
   }

   if (countTest == 5)
      printf("Test 10: Passed\n");
   else
      printf("Test 10: Failed\n");

/**************
 *
 * Test: Fill up file system with files and fail to write when full.
 *
 * Note: There are 40 blocks total (32 are still available now) thus 16 files
 *       will be written and on the 17 file open will fail.
 *
 **************/

   countTest = 0;

   printf("Test 11: Fill up file system with files and fail to write when full\n");
   char filename[9] = "";

   int fileDigit = 10;
   for (fileDigit = 10; ; fileDigit++) {

      if (fileDigit > 99) {
         break;
      }

      sprintf(filename, "myfile%d", fileDigit);

      // open file
      if ((fd = tfs_openFile(filename)) == -1) {
         //printf("tfs_openFile failed\n");
         break;
      }
      countTest++;

      //write some bytes
      if (tfs_writeFile(fd, tbuf1) == -1) {
         //printf("tfs_write failed\n");
         break;
      }
      countTest++;

      // close the file
      if (tfs_closeFile(fd) == -1) {
         printf("tfs_closeFile fd failed\n");
         exit(-1);
      }
      countTest++;
   }

   if (countTest == (3*16))
      printf("Test 11: Passed\n");
   else
      printf("Test 11: Failed\n");

/**************
 *
 * Test: Print all files in the filesystem.
 *
 **************/

   countTest = 0;

   printf("Test 12: Print all files in the filesystem.\n");

   printf("Files:\n");
   if (tfs_dir() == -1)
      printf("Test 12: Failed\n");
   else
      printf("Test 12: Passed\n");

/**************
 *
 * Test: Delete all of the files created in Test 11
 *
 * Note: There should be 16 files
 *
 **************/

   countTest = 0;

   printf("Test 13: Delete all of the files created in Test 11.\n");

   for (fileDigit = 10; fileDigit < 26; fileDigit++) {

      if (fileDigit > 99) {
         break;
      }

      memset(filename, 0, 9);
      sprintf(filename, "myfile%d", fileDigit);

      // open file
      if ((fd = tfs_openFile(filename)) == -1) {
         //printf("tfs_openFile failed\n");
         continue;
      }
      countTest++;

      // delete file
      if (tfs_deleteFile(fd) == -1) {
         //printf("tfs_delete failed\n");
         continue;
      }
      countTest++;

      // close the file
      if (tfs_closeFile(fd) == -1) {
         // close should fail since delete already closed the file.
         //printf("tfs_closeFile failed as expected\n");
         countTest++;
      }
   }

   if (countTest == (3*16))
      printf("Test 13: Passed\n");
   else
      printf("Test 13: Failed\n");

/**************
 *
 * Test: list all file, Rename file myfile02 to myfile03 and then relist all
 *       files.
 *
 **************/

   countTest = 0;

   printf("Test 14: list all file, Rename file myfile02 to myfile03 and then relist all files\n");

   printf("Files:\n");
   // list all files
   if (tfs_dir() != -1)
      countTest++;

   // open file
   if ((fd = tfs_openFile("myfile02")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   // rename file
   if (tfs_rename(fd, "myfile03") == -1) {
      puts("tfs_write failed");
      exit(-1);
   }
   countTest++;

   // close the file
   if (tfs_closeFile(fd) == -1) {
      printf("tfs_closeFile failed\n");
      exit(-1);
   }
   countTest++;

   printf("Files:\n");
   // list all files
   if (tfs_dir() != -1)
      countTest++;

   if (countTest == 5)
      printf("Test 14: Passed\n");
   else
      printf("Test 14: Failed\n");


   // CLEAN UP THIS TEST

   // open file
   if ((fd = tfs_openFile("myfile03")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }

   // rename file
   if (tfs_rename(fd, "myfile02") == -1) {
      puts("tfs_write failed");
      exit(-1);
   }

   // close the file
   if (tfs_closeFile(fd) == -1) {
      printf("tfs_closeFile failed\n");
      exit(-1);
   }

/**************
 *
 * Test: list creation time of myfile00
 *
 **************/

   countTest = 0;

   printf("Test 15: list creation time of myfile00\n");

   // open file
   if ((fd = tfs_openFile("myfile00")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   time_t time = -1;
   time = tfs_readFileInfo(fd);
   if (time != (time_t)-1) {
      countTest++;
   }

   printf("myfile00 creation time: %llu\n", (long long unsigned int)time);

   // close the file
   if (tfs_closeFile(fd) == -1) {
      printf("tfs_closeFile failed\n");
      exit(-1);
   }
   countTest++;

   if (countTest == 3)
      printf("Test 15: Passed\n");
   else
      printf("Test 15: Failed\n");

/**************
 *
 * Test: Make sure we can't write to a non-open file.
 *
 **************/

   countTest = 0;

   printf("Test 16: Make sure we can't write to a non-open file.\n");

   int badFD = 47002;

   // try to write some bytes to a closed file
   if (tfs_writeFile(badFD, tbuf1) == -1) {
      //printf("tfs_write failed\n");
      countTest++;
   }

   if (countTest == 1)
      printf("Test 16: Passed\n");
   else
      printf("Test 16: Failed\n");

/**************
 *
 * Test: Open file, seek 10 bytes into the file, write to seeked location, read file and close it
 *
 **************/

   countTest = 0;

   printf("Test 17: Open file, seek 10 bytes into the file, write to seeked location, read file and close it\n");

   //open the file again
   if ((fd = tfs_openFile("myfile00")) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   // seek into the file
   if (tfs_seek(fd, 10) == -1) {
      printf("tfs_seek failed\n");
      exit(-1);
   }
   countTest++;

   // write to file
   if (tfs_writeFile(fd, tbuf1) == -1) {
      printf("tfs_openFile failed\n");
      exit(-1);
   }
   countTest++;

   // read to end of the file
   char fileResult17[100] = "";
   i = 0;
   while(tfs_readByte(fd, &(fileResult17[i])) != -1) {
      if (fileResult17[i] == '\0') {
         break;
      }
      i++;
   }
   if (strcmp(fileResult17, tbuf1) == 0) {
      //printf("File Contents:\n[%s]\n", fileResult1);
      countTest++;
   }

   // close the file
   if (tfs_closeFile(fd) == -1) {
      printf("tfs_closeFile failed\n");
      exit(-1);
   }
   countTest++;

   if (countTest == 5)
      printf("Test 17: Passed\n");
   else
      printf("Test 17: Failed\n");

   printf("DONE WITH DEMO TEST\n");
   return 0;
}


