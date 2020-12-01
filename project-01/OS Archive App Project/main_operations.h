/* mkbkp.h 
 *
 * Yosef Hackmon
 *
 * provide handlers for saving a backup and extracting from a backup
 *
 */
#ifndef _MKBKP_H_
#define _MKBKP_H_


#include	<sys/types.h>
#include	<sys/stat.h>
#include        <fcntl.h>
#include        <stdlib.h>
#include        <stdio.h>
#include        <unistd.h>
#include	<string.h>
#include	<dirent.h>
#include 	<errno.h>
#include	<utime.h>
#include 	<sys/time.h>

#define SIZE_OF_FILE_HEADER 1024

#define FILE_ATTR_MAX_LENGTH_NAME_FIELD 256
#define FILE_ATTR_MAX_LENGTH_SIZE_FIELD 16
#define FILE_ATTR_MAX_LENGTH_PERMISSIONS_FIELD 8
#define FILE_ATTRMAX_LENGTH_MTIME_FIELD 16
#define FILE_ATTRMAX_LENGTH_MAGIC_FIELD 16

#define SIZE_OF_NAME 256
#define SIZE_OF_TYPE 16
#define SIZE_OF_MAGIC_NAME 16

#define SIZE_OF_CTIME_STR 32
#define SIZE_OF_ATIME_STR 32
#define SIZE_OF_MTIME_STR 32

#define SIZE_OF_TIME_STR 32

#define SIZE_OF_THIS_HEADER 4

#define SIZE_OF_NO_SUB_DIR 64
#define SIZE_OF_NO_REG_FILE 64
#define SIZE_OF_NO_SYM_LINK 64


#define INFO(msg) \
	fprintf(stderr, "info: %s:%d: ", __FILE__, __LINE__);\
	fprintf(stderr, "%s\n", msg);
/*
 we will the 
*/


//we save the attributes of the file as chars;
typedef struct file_attr {
	char name [SIZE_OF_NAME]; //name of the file, specified with the path 
	char type [SIZE_OF_TYPE]; //type of this file: directory, regular, symbolic link
	char magic_name [SIZE_OF_MAGIC_NAME]; //name of the program that made this archive, should be mkbkp
	//char name[FILE_ATTR_MAX_LENGTH_NAME_FIELD]; //the most important 
	char size[FILE_ATTR_MAX_LENGTH_SIZE_FIELD];	//hold the actual size of the file
	/*char permissions [FILE_ATTR_MAX_LENGTH_PERMISSIONS_FIELD];
	char mtime [FILE_ATTRMAX_LENGTH_MTIME_FIELD];
	char magic [FILE_ATTRMAX_LENGTH_MAGIC_FIELD];  //will let us know that the function 
	*/
	
	long long file_size;

	//From struct stat
	long st_ino;				//I-node number
	unsigned long st_mode; 			//Mode:	%lo (octal)
	long st_nlink;				//Link count
	long st_uid;				//Ownership: UID
	long st_gid;				//Ownership: GID
	long st_blksize;			//Preferred I/O block size (in bytes)
	long long st_size;			//File size (in bytes)
	long long st_blocks;			//Blocks allocated (for this file)

	time_t atime;
	time_t mtime;
	time_t ctime;
	
	//char st_ctime_str[SIZE_OF_CTIME_STR];	//last statuse change (as a string)
	//char st_atime_str[SIZE_OF_ATIME_STR];	//last file access (as a string)
	//char st_mtime_str[SIZE_OF_MTIME_STR];	//last file modificatin (as a string)
	
	char st_ctime_str[SIZE_OF_TIME_STR];	//last statuse change (as a string)
	char st_atime_str[SIZE_OF_TIME_STR];	//last file access (as a string)
	char st_mtime_str[SIZE_OF_TIME_STR];	//last file modificatin (as a string)

	//relevent only for Directory:

	long noRegFile; //how many regFiles in this directory

	long noSymLink; //how many symlinks this directory contains
	//number of sub directories (one level under the current dir;
	long noSubDir; //how many sub-directories (one level of nesting) is in this directory

	} file_attr_t;

typedef struct backup_info { 
	char name [SIZE_OF_NAME]; //name of the file, specified with the path 
	char type [SIZE_OF_TYPE]; //type of this file: directory, regular, symbolic link

	//char header_size [SIZE_OF_THIS_HEADER];
	
	char noSubDir[SIZE_OF_NO_SUB_DIR];
	char noRegFile [SIZE_OF_NO_REG_FILE];
	char noSymLink [SIZE_OF_NO_SYM_LINK];

	int sizeOfThisHeaderInBytes; 

	int totalSizeSubDir; //what is the total size in the disk (not include the headers)
	int totalSizeRegFile; 
	int totalSizeSymLink; 

	int permissions; //permissions of the file in octal way .. 

	
} backup_info_t;
	


int can_be_archived (char *backup_file, char *path);
int can_be_extracted (char *backup_file);
int regular_file_already_exist(char *fileName);

int do_archive (char *backup_file, char *path); //recursive call- call to one of the next calls
int handle_archive_directory_tree(int fd, char *pathname);
//int archive_directory (char *backup_file, char *path);
//int archive_regular_file (char *backup_file, char *path);
//int archive_symbolic_link (char *backup_file, char *path);

int my_do_extract1(int fd);
int extract_regular_file(int fd, file_attr_t *pfAttr);

int  create_the_missing_path(char *pathname);
size_t delete_the_trailing_slash_if_exist(char *pathname, char *resBuf,  int size);
int do_extract (char *backup_file); //recursive call

int handle_extract_tree(int fd, char *pAttrBuf);

int printFAttr(file_attr_t *pfAttr);
/*
 * getFileType()
 * PARAMS:
 * char *file_name - the file to exampine
 *
 * RET:
 * 0 - unknown (default)
 * 1 - regular
 * 2 - folder
 * 3 - symbolic link
 *
 */
int getFileType (char* file_name); 
int getHeaderFromFile(char *path, char *fAttrBuf);

 int archive_regular_file (int fd, char *path);
 int archive_directory (int fd, char *path);
long long handleDirContent(char *path, file_attr_t * pfAttr );

int handle_dir_contents(int fd, char *path);
int handle_dir_contents2(int fd, char *path);
int getStatAttr(file_attr_t *pfAttr, struct stat *sb);

int my_main(int argc, char **argv);
int my_main2(int argc, char **argv);

//general_operations.c
int  copyfileContent2(int fd_to_be_written, char *path);
int  copyContent(int fd_to_write_to, int fd_to_read_from, long long int amount);

void printError(int myerrno);
int print_directory_tree(char *pathname);





//funcWrappers_operations.c
//return value:
// on success - a pointer to the dirent structure
// on failure or if the end of the stream is reached: NULL 
// if the end of the directory sream is reached - return Null, but errno is not changed! 
// if an ERROR occures - return NULL but errno is set, we can scheck the values of errno! 
struct dirent *try_readdir(DIR *dirp);

//return a null if threre is an error, errno is set ..
//otherwise - point of type DIR *
 DIR *try_opendir(const char *name);

 int try_closedir(DIR *dirp);

//on success zero is returned
//on error -1 is return and errno set ..
 int try_chdir(const char *path);
int try_mkdir(const char *pathname, mode_t mode);


int try_close (int fd);
int try_creat(const char *pathname,  mode_t mode);
int try_open(const char *pathname, int flags, mode_t mode);
int try_stat(const char *path, struct stat *buf);
int try_lstat(const char *path, struct stat *buf);

ssize_t try_write(int fd, const void *buf, size_t count);
ssize_t try_read(int fd, void *buf, size_t count);
 /*
//
struct dirent *try_readdir(DIR *dirp);

//return a null if threre is an error, errno is set ..
 DIR *try_opendir(const char *name);
*/
//on success zero is returned
//on error -1 is return and errno set ..
 int try_chdir(const char *path);

mode_t try_umask(mode_t mask);
int try_chmod(const char *path, mode_t mode);
int try_chown(const char *path, uid_t owner, gid_t group);
int try_lchown(const char *path, uid_t owner, gid_t group);
int try_utime(const char *path, const struct utimbuf *times);


#endif /* _MKBKP_H_ */

