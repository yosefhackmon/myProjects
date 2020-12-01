/* other_operations.c */


//struct my_stat {
//   dev_t     st_dev;     /* ID of device containing file */
//    ino_t     st_ino;     /* inode number */
//    mode_t    st_mode;    /* protection */
//    nlink_t   st_nlink;   /* number of hard links */
//    uid_t     st_uid;     /* user ID of owner */
//    gid_t     st_gid;     /* group ID of owner */
//    dev_t     st_rdev;    /* device ID (if special file) */
//    off_t     st_size;    /* total size, in bytes */
//    blksize_t st_blksize; /* blocksize for file system I/O */
//   blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
//    time_t    st_atime;   /* time of last access */
//    time_t    st_mtime;   /* time of last modification */
//    time_t    st_ctime;   /* time of last status change */
//};

/*
struct my_stat {
    dev_t     st_dev;     // ID of device containing file 
    ino_t     st_ino;     // inode number 
    mode_t    st_mode;    // protection 
    nlink_t   st_nlink;   // number of hard links 
    uid_t     st_uid;     // user ID of owner 
    gid_t     st_gid;     // group ID of owner 
    dev_t     st_rdev;    // device ID (if special file) 
    off_t     st_size;    // total size, in bytes 
    blksize_t st_blksize; // blocksize for file system I/O 
    blkcnt_t  st_blocks;  // number of 512B blocks allocated 
    time_t    st_atime;   // time of last access 
    time_t    st_mtime;   // time of last modification 
    time_t    st_ctime;   // time of last status change 
};
*/
/*
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
*/
#include <time.h>
#include "main_operations.h"

int getFileType (char* file_name){

	//int		i;
	struct stat	buf;
	char		*ptr;
	int retVal = 0;
	char cwd[SIZE_OF_NAME];
	//for (i = 1; i < argc; i++) {
		//printf("%s: ", file_name);

		//printf("in other_operations: func getFileType: file_name is %s\n", file_name);

		if (lstat(file_name, &buf) < 0) {
			printf("IN LSTAT: ");
			printError(errno);
			printf("FAIL! in other_operations: func getFileType(), file_name is %s\n", file_name);
			getcwd(cwd,sizeof(cwd));
			printf("cwd is: %s\n", cwd);
			fflush(stdout);
			fprintf(stderr,"lstat error, exiting ...\n");
			exit(1);
		}
		//printf("in other_operations: func getFileType(), lstat finish gracefullY: file_name is %s\n", file_name);
			//continue;
		//}

		if      (S_ISREG(buf.st_mode))	{ptr = "regular"; retVal=1;}
		else if (S_ISDIR(buf.st_mode))	{ptr = "directory"; retVal=2;}
		else if (S_ISCHR(buf.st_mode))	{ptr = "character special";}
		else if (S_ISBLK(buf.st_mode))	{ptr = "block special";}
		else if (S_ISFIFO(buf.st_mode))	{ptr = "fifo";}
#ifdef	S_ISLNK
		else if (S_ISLNK(buf.st_mode))	{ptr = "symbolic link"; retVal=3;}
#endif
#ifdef	S_ISSOCK
		else if (S_ISSOCK(buf.st_mode))	{ptr = "socket";}
#endif
		else	{			ptr = "** unknown mode **";}
		//printf("%s\n", ptr);
		
		if(retVal==0){
				//TODO remove this debug info 
				INFO(ptr);
			}
			//printf("in function getFileType
	return retVal;
	
}


static int myFileType (char* file_name){

	//int		i;
	struct stat	buf;
	char		*ptr;
	char cwd [SIZE_OF_NAME];

	int retVal = 0;
	//for (i = 1; i < argc; i++) {
		printf("%s: ", file_name);
		if (lstat(file_name, &buf) < 0) {
			printf("in other_operations: func myFileType(), file_name is %s\n", file_name);
			getcwd(cwd,sizeof(cwd));
			printf("cwd is: %s\n", cwd);
			fflush(stdout);
			fprintf(stderr,"lstat error, exiting ..\n");
			exit(1);
		}
			//continue;
		//}

		if      (S_ISREG(buf.st_mode))	ptr = "regular";
		else if (S_ISDIR(buf.st_mode))	ptr = "directory";
		else if (S_ISCHR(buf.st_mode))	ptr = "character special";
		else if (S_ISBLK(buf.st_mode))	ptr = "block special";
		else if (S_ISFIFO(buf.st_mode))	ptr = "fifo";
#ifdef	S_ISLNK
		else if (S_ISLNK(buf.st_mode))	ptr = "symbolic link";
#endif
#ifdef	S_ISSOCK
		else if (S_ISSOCK(buf.st_mode))	ptr = "socket";
#endif
		else				ptr = "** unknown mode **";
		printf("%s\n", ptr);

	return retVal;
	
}


int my_main2(int argc, char *argv[]){


	int res = 0;
	long count = 0;
	char *file_name;

	DIR *dir;
	struct dirent *sd;

	/* TODO replace "." with the directory the file should be in*/
	dir = opendir("."); //open current working directory

	if(dir == NULL){
		printf("ERROR: in regular_file_already_exist(): Unable to open directory. exiting ...\n");
		exit(1);
	}

	while((sd = readdir(dir)) != NULL){
		/*
		if((strcmp(fileName, sd->d_name)) == 0){
			res = 1;
			break;
		}
		*/
	file_name = sd->d_name;
	count++;
	//printf("[%ld] %s\n", count, sd->d_name);
	printf("[%ld] ", count);
	myFileType(file_name);
	}

	if((closedir(dir)) <0){
		printf("ERROR in regular_file_already_exist(): Unable to close directory. exiting ...\n");
		exit(1);
	}	
	
	return res;
return 0;
}

int
//main(int argc, char *argv[])
my_main(int argc, char *argv[])
{
    struct stat sb;
/*
   if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
*/
   if (stat(argv[1], &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

   printf("File type:                ");

   switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }
/*
long st_ino;				//I-node number
unsigned long st_mode; 			//Mode:	%lo (octal)
long st_nlink;				//Link count
long st_uid;				//Ownership: UID
long st_gid;				//Ownership: GID
long st_blksize;			//Preferred I/O block size (in bytes)
long long st_size;			//File size (in bytes)
long long st_blocks;			//Blocks allocated (for this file)

char st_ctime_str[SIZE_OF_CTIME_STR];	//last statuse change (as a string)
char st_atime_str[SIZE_OF_ATIME_STR];	//last file access (as a string)
char st_mtime_str[SIZE_OF_MTIME_STR];	//last file modificatin (as a string)
*/
   printf("I-node number:            %ld\n", (long) sb.st_ino);

   printf("Mode:                     %lo (octal)\n",
            (unsigned long) sb.st_mode);

   printf("Link count:               %ld\n", (long) sb.st_nlink);
    printf("Ownership:                UID=%ld   GID=%ld\n",
            (long) sb.st_uid, (long) sb.st_gid);

   printf("Preferred I/O block size: %ld bytes\n",
            (long) sb.st_blksize);
    printf("File size:                %lld bytes\n",
            (long long) sb.st_size);
    printf("Blocks allocated:         %lld\n",
            (long long) sb.st_blocks);

   printf("Last status change:       %s", ctime(&sb.st_ctime));
    printf("Last file access:         %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));

	return 1;
   exit(EXIT_SUCCESS);
}
