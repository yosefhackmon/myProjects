/* extract_operations.c 
*
* Yosef Hackmon
*
* this file hold the function that starts the extraction opperations.
*
*
*/

//#include	"mkbkp.h"
#include	"main_operations.h"

//

static int fix_the_path(char *backup_file){

	int fd;
	
	file_attr_t fAttr, *pfAttr;
	char fAttrBuf[sizeof(fAttr)];
	ssize_t noBytesRead;
	
	//struct stat buf;	
	


	//open the file, test if it is regular, dir, symlink .. 
	if((fd = open(backup_file, O_RDONLY)) < 0){
		fprintf(stdout,"open error for file: %s, exiting ...",backup_file);
		exit(1);
	}
	
	//here we may want to create all the directories .. after that.. we shall return the position of the cursur to the begging..

	//my_do_extract1(fd);
	
//return 0;
	
	pfAttr = (file_attr_t *)fAttrBuf;
	//pfAttr = fAttrBuf;
	printf("sizeof(pfAttr)==%d\n", sizeof(pfAttr));
	memset(pfAttr, 0, sizeof(fAttr)); //the size of an header  // not needed! 

	//postcondition: noBytesRead have to be equal to sizeof(file_attr_t)
	if((noBytesRead =  read(fd, pfAttr, sizeof(file_attr_t))) < 0){
		fprintf(stderr,"read error\n");
		exit(1);
		}
	
	try_close(fd);

	//now i have the file attr! .. 
	//printf("pfAttr->name: == %s\n", pfAttr->name);
	create_the_missing_path(pfAttr->name);
	return 0;
}

int printFAttr(file_attr_t *pfAttr){
	return 0;
	printf("the name is %s\nthe type is %s\nthe magic_name is %s\nthe size (of original file) is %lld\n", pfAttr->name, pfAttr->type ,pfAttr->magic_name,pfAttr->file_size);
	
	printf("the sizeof header is %d\n\n", sizeof(file_attr_t));

	
	printf("the file st_ino is: %ld\n", pfAttr->st_ino);
	printf("the file st_mode is: %lo (octal)\n", (unsigned long)pfAttr->st_mode);
	printf("the file st_nlink is: %ld\n", pfAttr->st_nlink);
	printf("the file st_uid is: %ld\n", pfAttr->st_uid);

	printf("the file st_gid is: %ld\n", pfAttr->st_gid);
	printf("the file st_blksize is: %ld\n", pfAttr->st_blksize);
	printf("the file st_size is: %lld\n", pfAttr->st_size);
	printf("the file st_blocks is: %lld\n", pfAttr->st_blocks);

	return 0;
	
}
/*
 * 
 * Pre-condition: fd is open, position of the read: just after the header of our regular file in fd
 * TODO test precondition! 
 *
 *
*/
 int extract_regular_file(int fd, file_attr_t *pfAttr){
	//TODO test that we are checking the right directory .. 
	struct utimbuf  times;
	int fd_to_write_to;
	int fd_to_read_from = fd;

	//int counter = 0;
	int amount = pfAttr->st_size;
	// umask( S_IWGRP | S_IWOTH);
	// if ((fd = open(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
		
		//search that the file is not exist!! 
		if((regular_file_already_exist(pfAttr->name)) != 0){
			printf("already exists %s: File exist, exiting ...\n", pfAttr->name);

			if((close(fd)) < 0)
				fprintf(stdout,"close error - unable to close file: %s",pfAttr->name);

			exit(1);
		}

		if( (fd_to_write_to = open(pfAttr->name, O_CREAT | O_APPEND | O_WRONLY, pfAttr->st_mode)) < 0){
                fprintf(stdout,"open error for file: %s",pfAttr->name);
		
		//TODO close fd before exiting .. 
	
		if((close(fd)) < 0)
			fprintf(stdout,"open error for file: %s",pfAttr->name);

		exit(1);
		}
		
		//retrive the file status 
		//struct utimbuf  times;
		try_lchown(pfAttr->name, pfAttr->st_uid, pfAttr->st_gid);
		
		times.actime = pfAttr->atime;
		times.modtime = pfAttr->mtime;
		try_utime(pfAttr->name, &times);


		//utime(pfAttr->name, pfAttr->st_
	//counter = copyContent(fd_to_write_to, fd_to_read_from, amount);
	copyContent(fd_to_write_to, fd_to_read_from, amount);
	
	if((close(fd_to_write_to)) < 0){
		fprintf(stdout, "close error for a file, exiting ... \n");
		exit(1);
	}

	//TODO
	return 0;
}

static int extract_directory(int fd, file_attr_t *pfAttr){
	
	//handle_extract_tree(fd,(char *)pfAttr);
	//TODO
	return 0;
}

static int extract_symbolic_link(int fd, file_attr_t *pfAttr){
	
	//TODO
	return 0;
}

	/*

static int create_new_regular_file(char *regularfileNane){
	
	int fd;

	//we start with .. 
	fd = create_new_file(); 

	return fd;

}

static int extract_regular_file(char *backupedRegular){
	//take the name from the start
	//take the size as long long
	//then the create new file, open it, write down the size .. 
	int fd;
	
	file_attr_t fAttr, *pfAttr;
	char fAttrBuf[sizeof(fAttr)];

	pfAttr = (file_attr_t *)fAttrBuf;
	memset(pfAttr, 0, sizeof(fAttr)); //the size of an header 

	if (fd = open(backupedRegular);
	memcpy(pfAttr->name, path, strlen(path)); //copy from the path into the buffer .. 

	int fd;

	//we open a new file in the directory we want .. for now it is the currentWorkingDir..

	//TODO test that there is no file named as the name of our file in the dir.. 
	fd = create_new_regular_file(backupedRegular);

	
	//TODO
	return 0;
}
*/
//A recursive function
/*
 * the function have one parameter: backupfile (as a string)
 * we open the backupfile ..
 * we test if it is ours, 
 * we test what kind is it?
 *
 *
 *
*/

int do_extract (char *backup_file){
	//TODO	

	int fd;
	
	file_attr_t fAttr, *pfAttr;
	char fAttrBuf[sizeof(fAttr)];
	ssize_t noBytesRead;
	
	//struct stat buf;	
	
	fix_the_path(backup_file);


	//open the file, test if it is regular, dir, symlink .. 
	if((fd = open(backup_file, O_RDONLY)) < 0){
		fprintf(stdout,"open error for file: %s, exiting ...",backup_file);
		exit(1);
	}
	
	//here we may want to create all the directories .. after that.. we shall return the position of the cursur to the begging..

	my_do_extract1(fd);
	return 0;
	
	pfAttr = (file_attr_t *)fAttrBuf;
	//pfAttr = fAttrBuf;
	//printf("sizeof(pfAttr)==%d\n", sizeof(pfAttr));
	memset(pfAttr, 0, sizeof(fAttr)); //the size of an header  // not needed! 

	//postcondition: noBytesRead have to be equal to sizeof(file_attr_t)
	if((noBytesRead =  read(fd, pfAttr, sizeof(file_attr_t))) < 0){
		fprintf(stderr,"read error\n");
		exit(1);
		}

	//now we can extract all the data that we need! 
	//the name ..
	//the size .. (without the header)! 
	//the type ..
	//printf("\n in extract\n\n");
	
	printFAttr(pfAttr);
	//print_extract_treint fd, 

//	handle_extract_tree(fd,(char *)pfAttr);
	
	//now we should read the data, let's try it ..  
	//we need a char buf for the 

	//here we open the file and test that this is ours, the size must be at least as header! 
	//TODO here we should make some check! 
	if((strcmp(pfAttr->type, "regular")) == 0){
		extract_regular_file(fd, pfAttr);
	} else if ((strcmp(pfAttr->type, "directory")) == 0){
		extract_directory(fd, pfAttr);
	} else if ((strcmp(pfAttr->type, "symbolic link")) == 0){
		extract_symbolic_link(fd, pfAttr);
	} else {
		printf("ERROR: in do_extract: can't recognize the file type, exiting ...\n");
		exit(1);
	}
	
	//extract_regular_file(backup_file);

	if((close(fd)) < 0){
		fprintf(stdout, "close error for a file, exiting ... \n");
		exit(1);
	}

	return 0;
}


