/* print_operations.c */

#include "main_operations.h"

void printError(int myerrno){
switch(myerrno){
		case EACCES: printf("EACCES\n"); break;
		case EFAULT: printf("EFAULT\n"); break;
		case ENOENT: printf("ENOENT - The file does not exist.\n"); break;
		case ENOTDIR: printf("ENOTDIR -A component of path is not a directory.\n"); break;
		default: printf("UNKNOWN ISSUE\n");
		}

}
//static int i = 0;
static int shouldExecFunc_printSize = 0;

void printsize(int argc, char **argv){
	if(shouldExecFunc_printSize == 0);
		return;

	off_t st_size;
	struct stat buf;

	if(argc==4){
	if (lstat(argv[3], &buf) < 0) {
			fprintf(stderr,"lstat error");
			exit(1);
		}
	st_size = buf.st_size;
	printf("number of bytes in the file %s, is %d\n", argv[3], (int)st_size);

	uid_t uid = buf.st_uid;
	ino_t ino = buf.st_ino; //number of i-node

	time_t atime = buf.st_atime;
	time_t mtime = buf.st_mtime;
	time_t ctime = buf.st_ctime;

	printf("uid: %d, ino: %ld,  atime: %ld, mtime: %ld, ctime: %ld\n", (short)uid, (long)ino,(long)atime, (long)mtime, (long)ctime);
	fflush(stdout);

	}
}
