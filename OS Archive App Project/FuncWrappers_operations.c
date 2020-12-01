/* funcWrappers_operations.c 
 *
 * Yosef Hackmon
 *
 *
 * This File Provides wrappers to the file-system related functions we are about to use in our code.
 * 
 *  The purposes of the Wrappers: is to make sure that every call to a function/system-call such as open(), close(), lstat() etc. 
 *  	make sure every system call is made.
 *
 *
 *
 *
 */
#include "main_operations.h"
#include <errno.h>

/* funcWrappers_operations.c */




/* 
 * note: 
 *  creat()    is    equivalent   to   open()   with   flags   equal   to
 *     O_CREAT|O_WRONLY|O_TRUNC.
 *
 *
 *
 * Type of flags:
 *
 * 	(flags that set the file) Access mode:
 *		O_RDONLY, O_WRONLY, O_RDWR
 *		amount: 1 (exactly)
 *			
 * 		this will tell what operations we cad preform on the opened file.
 * 	
 * 	(!) the next two groups: #Creation-flags, #Status-flags have a distinction: 
 *				while the file #Status-flags can be retrived and (in some cases) modified using @fcntl(2),
 *				the Creation-flags may not! 
 *
 *				
 * 	file creation flags:
 *		*O_CREAT*, *O_EXCL*, *O_TRUNC*, (O_NOCTTY)
 *		amount >= 0. (can be bitwise-or'd)
 *
 *
 *		O_CREAT
 *
 *
 *
 *		O_EXCL 
 *	 	Ensure that this call creates the file: if this flag is speci‐
 *              fied in conjunction with O_CREAT, and pathname already exists,
 * 	        then open() will fail.
 *
 *	        When  these  two  flags  are specified, symbolic links are not
 *              followed: if pathname is a symbolic link,  then  open()  fails
 *              regardless of where the symbolic link points to.
 *
 *              In  general, the behavior of O_EXCL is undefined if it is used
 *              without O_CREAT. 
 *
 *
 *
 *		O_TRUNC:
			 If the file already exists and is a regular file and the  open
              mode  allows  writing (i.e., is O_RDWR or O_WRONLY) it will be
              truncated to length 0.
 *
 *
 *	file status flags:
 *		 *O_APPEND*, *O_LARGEFILE*, *O_NOATIME*, O_NOFOLLOW, (O_DIRECTORY)
 *	
 *		 O_APPEND 
 * 			The file is opened in append mode.  Before each write(2),  the
 *        	      file  offset  is positioned at the end of the file, as if with
 *        	      lseek(2).
 *	
 *		 O_LARGEFILE
 *             		(LFS)  Allow  files  whose  sizes  cannot be represented in an
 *             		off_t (but can be represented in an  off64_t)  to  be  opened
 *
 *		 O_NOATIME
 *			Do  not  update  the  file  last  access time (st_atime in the
 *	            	inode) when the file is read(2).
 *
 *		 O_NOFOLLOW
 *			If pathname is a symbolic link, then the open fails
 *			Symbolic links in earlier components of the pathname
 *              	will still be followed.
 *	
 *
 *
 *
 *
 *
 *		 O_APPEND
 *      	      The file is opened in append mode.  Before each write(2),  the
 *        	      file  offset  is positioned at the end of the file, as if with
 *        	      lseek(2).  O_APPEND may lead to corrupted files  on  NFS  file
 *        	      systems  if  more  than  one process appends data to a file at
 *        	      once.  This is because NFS does not  support  appending  to  a
 *        	      file,  so the client kernel has to simulate it, which can't be
 *        	      done without a race condition.
 * 
 *
 *		
 *		  O_CREAT
              If the file does not exist it  will  be  created.   The  owner
              (user  ID)  of the file is set to the effective user ID of the
              process.  The group ownership (group ID) is set either to  the
              effective  group  ID  of the process or to the group ID of the
              parent directory (depending on  file  system  type  and  mount
              options,  and  the mode of the parent directory, see the mount
              options bsdgroups and sysvgroups described in mount(8)).

              mode specifies the permissions to use in case a  new  file  is
              created.  This argument must be supplied when O_CREAT is spec‐
              ified in flags; if O_CREAT is  not  specified,  then  mode  is
              ignored.   The  effective  permissions  are  modified  by  the
              process's umask in the usual way: The permissions of the  cre‐
              ated  file  are  (mode & ~umask).   Note  that  this mode only
              applies to future accesses of  the  newly  created  file;  the
              open()  call  that  creates a read-only file may well return a
 *            read/write file descriptor.
 *
 *	       O_EXCL 
 * 		Ensure that this call creates the file: if this flag is speci‐
 *              fied in conjunction with O_CREAT, and pathname already exists,
 * 	        then open() will fail.
 *
 *	        When  these  two  flags  are specified, symbolic links are not
 *              followed: if pathname is a symbolic link,  then  open()  fails
 *              regardless of where the symbolic link points to.
 *
 *             In  general, the behavior of O_EXCL is undefined if it is used
 *             without O_CREAT. 				
 * 
 * 		
 *		O_NOFOLLOW
 *              	If pathname is a symbolic link, then the open fails.  This  is
 *              	a  FreeBSD  extension,  which  was  added  to Linux in version
 *              	2.1.126.  Symbolic links in earlier components of the pathname
 *              	will still be followed.
 *
 *		O_NOATIME
 *			Do  not  update  the  file  last  access time (st_atime in the
 *	            inode) when the file is read(2).  This flag  is  intended  for
 *	             use by indexing or backup programs, where its use can signifi‐
 *	             cantly reduce the amount of disk activity.  This flag may  not
 *	             be  effective  on all file systems.  One example is NFS, where
 *	             the server maintains the access time.
 *
 *
 *		O_LARGEFILE
              (LFS)  Allow  files  whose  sizes  cannot be represented in an
              off_t (but can be represented in an  off64_t)  to  be  opened.
              The  _LARGEFILE64_SOURCE macro must be defined (before includ‐
              ing any header files) in  order  to  obtain  this  definition.
              Setting the _FILE_OFFSET_BITS feature test macro to 64 (rather
              than using O_LARGEFILE) is the preferred method  of  accessing
              large files on 32-bit systems (see feature_test_macros(7)).
 *
 * 
*/
ssize_t try_write(int fd, const void *buf, size_t count);
ssize_t try_read(int fd, void *buf, size_t count);

int try_close (int fd);
int try_creat(const char *pathname,  mode_t mode);
int try_open(const char *pathname, int flags, mode_t mode);
int try_stat(const char *path, struct stat *buf);
int try_lstat(const char *path, struct stat *buf);
 
//return value:
// on success - a pointer to the dirent structure
// on failure or if the end of the stream is reached: NULL 
// if the end of the directory sream is reached - return Null, but errno is not changed! 
// if an ERROR occures - return NULL but errno is set, we can scheck the values of errno! 
struct dirent *try_readdir(DIR *dirp);
int try_mkdir(const char *pathname, mode_t mode);

//return a null if threre is an error, errno is set ..
//otherwise - point of type DIR *
 DIR *try_opendir(const char *name);

//return 0 on success, -1 on error (and errno is set)
 int try_closedir(DIR *dirp);

//on success zero is returned
//on error -1 is return and errno set ..
 int try_chdir(const char *path);


mode_t try_umask(mode_t mask);
int try_chmod(const char *path, mode_t mode);
int try_chown(const char *path, uid_t owner, gid_t group);
int try_lchown(const char *path, uid_t owner, gid_t group);

//test: should we wrap this func?
int try_utime(const char *path, const struct utimbuf *times);

//this function-call always succed, return value: the previous value of the mask.
 mode_t try_umask(mode_t mask){
	return umask(mask);
}
//chmod()  changes the permissions of the file specified whose pathname is given in path, which is dereferenced if it is a symbolic link.
//on success: 0 is returned.
//on error: -1 is returned, err is set.
int try_chmod(const char *path, mode_t mode){
	int retVal;
 	if((retVal =  chmod(path, mode)) < 0){
		fprintf(stderr,"chmod error. exiting ...\n");
		exit(1);
		}

	 return retVal;
}

// The  chown()  function  shall  change the user and group ownership of a file.
//  RETURN VALUE:
//	Upon successful completion, 0 shall be returned; otherwise, -1 shall be
//      returned and errno set to indicate the error. If  -1  is  returned,  no
//      changes are made in the user ID and group ID of the file.

int try_chown(const char *path, uid_t owner, gid_t group){
	int retVal;
 	if((retVal =  chown(path, owner, group)) < 0){
		fprintf(stderr,"chown error. exiting ...\n");
		exit(1);
		}

	 return retVal;
}
/*
DESCRIPTION
       The  lchown()  function  shall  be equivalent to chown(), except in the
       case where the named file is a symbolic link. In  this  case,  lchown()
       shall  change  the  ownership  of  the symbolic link file itself, while
       chown() changes the ownership of the file or  directory  to  which  the
       symbolic link refers.

RETURN VALUE
       Upon  successful  completion,  lchown()  shall  return 0. Otherwise, it
       shall return -1 and set errno to indicate an error.
*/
int try_lchown(const char *path, uid_t owner, gid_t group){
	int retVal;
 	if((retVal =  chown(path, owner, group)) < 0){
		fprintf(stderr,"lchown error. exiting ...\n");
		exit(1);
		}

	 return retVal;
}
/*
DESCRIPTION
       The utime() function shall set the access and modification times of the
       file named by the path argument.

ETURN VALUE
       Upon successful completion, 0 shall be returned. Otherwise, -1 shall be
       returned  and  errno  shall  be set to indicate the error, and the file
       times shall not be affected.
*/
int try_utime(const char *path, const struct utimbuf *times){
int retVal;
 	if((retVal =  utime(path, times)) < 0){
		fprintf(stderr,"utime error. exiting ...\n");
		exit(1);
		}

	 return retVal;
}

ssize_t try_read(int fd, void *buf, size_t count){
	ssize_t retVal;
 	if((retVal =  read(fd, buf, count)) < 0){
		fprintf(stderr,"Read error. exiting ...\n");
		exit(1);
		}

	 return retVal;
}
ssize_t try_write(int fd, const void *buf, size_t count){

 ssize_t retVal;
 if((retVal =  write(fd, buf, count)) < 0){
	fprintf(stderr,"write error. exiting ...\n");
	exit(1);
		}

 return retVal;
}

/* 
 * note: 
 *  creat()    is    equivalent   to   open()   with   flags   equal   to
 *     O_CREAT|O_WRONLY|O_TRUNC.
 *
 *
 */
int try_chdir(const char *path){
int retVal;
if ((retVal = chdir(path)) < 0){
		fprintf(stderr, "chdir error! exiting ... \n");
	
		switch(errno){
		case EACCES: printf("EACCES\n"); break;
		case EFAULT: printf("EFAULT\n"); break;
		case ENOENT: printf("ENOENT - The file does not exist.\n"); break;
		case ENOTDIR: printf("ENOTDIR -A component of path is not a directory.\n"); break;
		default: printf("UNKNOWN ISSUE\n");
		}

		exit(1); 
		}

	return retVal;


}

int try_creat(const char *pathname,  mode_t mode){
	int retVal;
	if ((retVal = creat(pathname, mode)) < 0){
		fprintf(stderr, "creat error! exiting ... \n");
		exit(1); 
		}

	return retVal;
}

int try_open(const char *pathname, int flags, mode_t mode) {
	int retVal;
	if ((retVal = open(pathname, flags, mode)) < 0){
		fprintf(stderr, "open error! exiting ... \n");
		exit(1); 
		}

	return retVal;
}

 int try_close (int fd){
	int retVal;
	if ((retVal = close(fd)) < 0){
		fprintf(stderr, "close error! exiting ... \n");
		exit(1); 
		}

	return retVal;
}

int try_lstat(const char *path, struct stat *buf){
	int retVal;
	if ((retVal = lstat(path, buf)) < 0) {
			fprintf(stderr,"lstat error, exiting ,, ");
			exit(1);
		}
	return retVal;
}

int try_stat(const char *path, struct stat *buf){
	int retVal;
	if ((retVal = stat(path, buf)) < 0) {
			fprintf(stderr,"lstat error, exiting ,, ");
			exit(1);
		}
	return retVal;
}
//return value: on error - null is returned
DIR *try_opendir(const char *name){
	DIR *retVal;
	if ((retVal = opendir(name)) == NULL) {
			fprintf(stderr,"opendir error, exiting ...\n");
			exit(1);
		}
	return retVal;
}

//null return - sometimes if it is not an error, thus we should check
//it may return if the end of the stream is reached as well
 struct dirent *try_readdir(DIR *dirp){
 struct dirent *retVal;
//TODO we should save errno! 
 int last_errno = errno; 


if ((retVal = readdir(dirp)) == NULL) {
			if(last_errno != errno){
			fprintf(stderr,"readdir error, exiting ...\n");
			exit(1);
			}
		}
	return retVal;

}

 int try_closedir(DIR *dirp){
	int retVal;
	if ((retVal = closedir(dirp)) < 0) {
			fprintf(stderr,"closedir error, exiting ...\n");
			exit(1);
		}
	return retVal;
}
/*
DESCRIPTION
       mkdir() attempts to create a directory named pathname.

       The  argument mode specifies the permissions to use.  It is modified by
       the process's umask in the usual way: the permissions  of  the  created
       directory  are  (mode & ~umask & 0777).  Other mode bits of the created
       directory depend on the operating system.  For Linux, see below.

       The newly created directory will be owned by the effective user  ID  of
       the process.  If the directory containing the file has the set-group-ID
       bit set, or if the file system is  mounted  with  BSD  group  semantics
       (mount -o bsdgroups or, synonymously mount -o grpid), the new directory
       will inherit the group ownership from its parent; otherwise it will  be
       owned by the effective group ID of the process.

       If  the  parent directory has the set-group-ID bit set then so will the
       newly created directory.

	RETURN VALUE
	       	mkdir() returns zero on success, or -1 if an error occurred  (in  which
       		case, errno is set appropriately).



*/
int try_mkdir(const char *pathname, mode_t mode){
	int retVal;
	if ((retVal = mkdir(pathname, mode)) < 0) {
			fprintf(stderr,"mkdir error, exiting ...\n");
			exit(1);
		}
	return retVal;
}
