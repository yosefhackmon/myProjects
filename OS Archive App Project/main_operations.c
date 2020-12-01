/* mkbkp.c 
 * "main.c"
 *
 * Yosef Hackmon
 *
 *
 * this file contains the main function of the program, retrive the arguments, checks that the usage was correct and act accordingly
 * 
 * 
 */


#include	"main_operations.h"

/*
 * 
 *
 *
 *
 */

char *correct_argv_format = "Usage: mkbkp <-c|-x> <backup_file> [file_to_backup | directory_to_backup]\n";

static void print_correct_argv_format(){
	printf("%s\n", correct_argv_format);
}

static void handle_incorrect_argv_format(){
	print_correct_argv_format();
	exit(1);
}
/*
void printsize(int argc, char **argv){
	
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
*/
/*
 *
 * if	argc == 3 && 
 * 		argv[0] = "./mkbkp"  
 *			argv[1] == "-x" && //compare strings!
 *				isValidBackupFile(argv[2]) //the path is ok, magic-numbers is ok, we wrapped it! - we are the owner!
 *
 *
 *	then	=> extract(argv[2])	//i.e.	case(filetype(argv[2]))
 *						regular-file:	extract-regular(argv[2])
 *						symblic-link:	extract-symlink(argv[2])
 *						directory:	extract-dir(argv[2])
 *
 *
 *
 *
 *
 * if argc == 4 &&
 *		argv[1] == "-c"
 *			argv[2] is an existing file //and then what?, or new file - and then it is good!
 *				argv[3] is have to be existing file! dir, regular or symlink!
 *
 *			
 *
 *	
 *	if (regular) => handle regular! 
 *	if  
 * 
 *
 * 
 * 
 *
 */
int main (int argc, char *argv[]) {
	
	
	if(argc < 3 || argc > 4)
		handle_incorrect_argv_format();
	
	
	if (argc == 3){
		if(!(strcmp(argv[1], "-x"))){
			if(can_be_extracted(argv[2]))
				do_extract(argv[2]);
		} else {
			handle_incorrect_argv_format();
		}
	}
			//check that argv[2] is valid (the file exist, and we can extract it (magic chars - saying it was created by mkbak)
	
	if (argc == 4){
		if(!(strcmp(argv[1], "-c"))){
			//check that argv[2] is valid
			/*printsize(argc, argv);*/
			if(can_be_archived(argv[2], argv[3]))
				do_archive(argv[2], argv[3]);
		} else {
			handle_incorrect_argv_format();
		}
	}
			//we creating the file if not exist and override it if it does! 
			//handle_incorrect_argv_format();
			
	return 0;
}
