/* validiation_operations.c
 *
 * Yosef Hackmon
 *
 * Checks for the validity of the user's input (as defined below)
 *
 *
 */

//#include	"mkbkp.h"
#include	"main_operations.h"

// static char *archiving_failed_msg1 = "archiving failed - can't archive an archive file\n";

/* 
 * test that backup_file != path (if both files) //they are not the same .. 
 * 
 * if (backup_file == path) => then if the file exist: it is living the file with length0, we are exiting with a message!
 *
 *	case 1:
 * ./mkbkp -c example.txt example.txt	=>
 *		archiving failed - can't archive an archive file
 * 
 * 	it suppose to have example.txt (even  if it wasn't exist prior to the call) with length 0 in the directory! 
 *
 */
//int isBackupable (char *backup_file, char *path){
int can_be_archived (char *backup_file, char *path){
	//TODO test if the object  specified by path is of type file/directory/symbolic_link 
	//backup_file is extractable

	return 1;
}

/* input must be of type:  3 <= argc <= 4 
 *
 * if(argc == 3) => strcmp(argv[1], "-x") == 0
 *
 * the file is extractable if WE created it with our program
 * the size is at least the size of header!! (thus we can relay on the data), no seg fault!
 */

 //int isExtractable (char *backup_file){

int can_be_extracted (char *backup_file){
	

	return 1;
}


int regular_file_already_exist(char *fileName){
	
	
	int res = 0;	
	DIR *dir;
	struct dirent *sd;

	/* TODO replace "." with the directory the file should be in*/
	dir = opendir("."); //open current working directory

	if(dir == NULL){
		printf("ERROR: in regular_file_already_exist(): Unable to open directory. exiting ...\n");
		exit(1);
	}

	while((sd = readdir(dir)) != NULL){
		if((strcmp(fileName, sd->d_name)) == 0){
		res = 1;
		break;
		}
	}

	if((closedir(dir)) <0){
		printf("ERROR in regular_file_already_exist(): Unable to close directory. exiting ...\n");
		exit(1);
	}	
	
	return res;
}

#include	<sys/types.h>
#include	<sys/stat.h>
#include        <stdio.h>

char *
filetype(char *file)
{
	//int		i;
	struct stat	buf;
	char		*ptr;

	if (lstat(file, &buf) < 0) {
		fprintf(stderr,"lstat error");
		exit(1);
		}

		if      (S_ISREG(buf.st_mode))	ptr = "regular";
		else if (S_ISDIR(buf.st_mode))	ptr = "directory";
		//else if (S_ISCHR(buf.st_mode))	ptr = "character special";
		//else if (S_ISBLK(buf.st_mode))	ptr = "block special";
		//else if (S_ISFIFO(buf.st_mode))	ptr = "fifo";
#ifdef	S_ISLNK
		else if (S_ISLNK(buf.st_mode))	ptr = "symbolic link";
#endif

		else				ptr = "** unknown mode **";

		return ptr;

}
