
README
------
TinyFS is a simple file system.


AUTHORS
-------
* Douglas Brandt
* Kerry S.


NOTES
-----
Completion Status:  This program is fully functional.

Per our design:

* We intentionally mount and unmount the disk/filesystem when there are no
  files open.
* tfs_delete() deletes the file and inode and closes the associated file
  description.
* The disk does not support multi-threaded/multi-process access.
* We enforce mandatory file locking to avoid problems with multiple file
  descriptors being open and one of them deleting the file.
* The file name length must be between 1 and 8 characters.  Our file system
  only detects corruption when opening the disk.  At that time, it checks the
  magic number in the super block only and will proceed forward if that number
  is correct or reformat the whole file system if that number is incorrect.

