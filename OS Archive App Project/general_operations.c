/* general_operations.c 
 *
 * Yosef Hackmon
 *
 *
 * This file contains  function to be used by both extract and archive methods 
 * 
 *
 * 
 *
 */ 


#include "main_operations.h"

int  copyContent(int fd_to_write_to, int fd_to_read_from, long long int amount){
	//todo change the mask to feet the right one! 
	
	
	int readRetVal = 0;
	int writeRetVal;

	char buf;
	//ssize_t count;
	long long int counter = 0; //count how many bytes read so far
	// umask( S_IWGRP | S_IWOTH);
	// if ((fd = open(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
	/*	
	if( (fd1 = open(path, O_RDONLY)) < 0){
                fprintf(stdout,"open error for file: %s",path);
		exit(1);
		}
	*/
	//bad condition! we can't tell if this is the end of file! 
	//while ((read(fd1, &buf, 1)) != EOF){
	while (counter < amount && ((readRetVal = read(fd_to_read_from, &buf, 1)) > 0) ){
		
		writeRetVal = write(fd_to_write_to, &buf, 1);

		if(writeRetVal < 0){//error in write
			fprintf(stderr, "ERROR, write fail! exiting ... \n");
			exit(1); 
		}
		//fflush(fd_to_be_written);
		counter++;	
	}
	
	if(readRetVal < 0){//error reading
		fprintf(stderr, "ERROR, read fail! exiting ... \n");
		exit(1); 	
	}
		

	
	
	//printf("the number of chars in path is: %d\n", counter);
	printf("In copyContent: the number of bytes copied to fd_to_write is: %lld\n", counter);
	fflush(stdout);
	
	
	/*
	if ((close(fd1)) < 0){
		fprintf(stderr, "close error! exiting ... \n");
		exit(1); 
		}
	*/
	return counter; 	
	//TODO 
	//return 0;
	
}	

int  copyfileContent2(int fd_to_be_written, char *path){
	//todo change the mask to feet the right one! 
	
	struct stat	buf;

	
	
	//char buf;
//	int readRetVal;
//	int writeRetVal;

	int fd1; 
	//ssize_t count;
	long long int amount;// counter = 0; //count how many bytes read so far

	int counter = 0;
	// umask( S_IWGRP | S_IWOTH);
	// if ((fd = open(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
		if (lstat(path, &buf) < 0) {
			fprintf(stderr,"lstat error");
			exit(1);
		}


		amount = buf.st_size;
		printf("int: %s: %d :%sint amount is %lld\n",__FILE__, __LINE__, __FUNCTION__,  amount);

		if( (fd1 = open(path, O_RDONLY)) < 0){
                fprintf(stdout,"open error for file: %s",path);
		exit(1);
		}

	counter = copyContent(fd_to_be_written, fd1, amount);
	
/*
		

	//bad condition! we can't tell if this is the end of file! 
	//while ((read(fd1, &buf, 1)) != EOF){
	while ((readRetVal = read(fd1, &buf, 1)) > 0 ){
		
		writeRetVal = write(fd_to_be_written, &buf, 1);

		if(writeRetVal < 0){//error in write
			fprintf(stderr, "ERROR, write fail! exiting ... \n");
			exit(1); 
		}
		//fflush(fd_to_be_written);
		counter++;	
	}
	
	if(readRetVal < 0){//error reading
		fprintf(stderr, "ERROR, read fail! exiting ... \n");
		exit(1); 	
	}
		
	//buf = EOF;
	//write(fd_to_be_written, &buf, 1);
	
	*/
	printf("the number of chars in path is: %d\n", counter);
	fflush(stdout);
	
	
	
	if ((close(fd1)) < 0){
		fprintf(stderr, "close error! exiting ... \n");
		exit(1); 
		}
	
	return counter; 	
	//TODO 
	//return 0;
	
}

/*
 * create new file in the current working directory ..
 *
 *
 */
//file creation: when we backup start a new file 
/*
 int create_new_file(char *path){

	umask(0); 
        if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)
                fprintf(stderr,"creat error for foo");

	int fd = open(


 }
*/
/*
int copyBuffer(char *buf1, char *buf2, int version){

}
*/


/*
 * copy the file content given by path (not yet open)
 * read it and copy to the file given by fd_to_be_written (i.e. it is already open)
 * assume path is not yet open, we are
 *
 *
 *
 *
*/
//getStatAttr
//static int copyStatBufferIntoFAttrBuffer(file_attr_t *pfAttr, struct stat *sb){
 int getStatAttr(file_attr_t *pfAttr, struct stat *sb){
/*
	long st_ino;				//I-node number
	unsigned long st_mode; 			//Mode:	%lo (octal)
	long st_nlink;				//Link count
	long st_uid;				//Ownership: UID
	long st_gid;				//Ownership: GID
	long st_blksize;			//Preferred I/O block size (in bytes)
	long long st_size;			//File size (in bytes)
	long long st_blocks;			//Blocks allocated (for this file)
*/
	pfAttr->st_ino = sb->st_ino;
	pfAttr->st_mode = sb->st_mode;
	pfAttr->st_nlink = sb->st_nlink;
	pfAttr->st_uid = sb->st_uid;

	pfAttr->st_gid = sb->st_gid;
	pfAttr->st_blksize = sb->st_blksize;
	pfAttr->st_size = sb->st_size;
	pfAttr->st_blocks = sb->st_blocks;

	pfAttr->atime = sb->st_atime;
	pfAttr->mtime = sb->st_mtime;
	pfAttr->ctime = sb->st_ctime;
	
	return 0;

}

int getHeaderFromFile(char *path, char *fAttrBuf){

file_attr_t fAttr, *pfAttr;
	
	int fType = getFileType(path);

	struct stat buf;

	
	if (lstat(path, &buf) < 0) {
			fprintf(stderr,"lstat error");
			exit(1);
		}
	
	pfAttr = (file_attr_t *)fAttrBuf;
	
	memset(pfAttr, 0, sizeof(fAttr)); //the size of an header 

	
	//copy the name given to pathName
	memcpy(pfAttr->name, path, strlen(path)); //copy from the path into the buffer .. 

	
	if(fType == 1){
	memcpy(pfAttr->type, "regular", strlen("regular"));
	} else if (fType == 2) {
	memcpy(pfAttr->type, "directory", strlen("directory"));
	} else if (fType == 3) {
	memcpy(pfAttr->type, "symbolic link", strlen("symbolic link"));
	} else {
		//fType == 0 => thus Unknown type
		//TODO in case of unknown file, what to do ..
		printf("ERROR: in func getHeaderFromFile: type of %s is unknown! exiting ... \n", path);
		exit(1);
	}

	memcpy(pfAttr->magic_name, "mkbkp", strlen("mkbkp"));

		//write the buf (struct stat) info into the file ..
		//TODO change it to avoid copy twice .. 
	
		pfAttr->file_size = buf.st_size;
	
	//string operations to copy the content 
	getStatAttr(pfAttr, &buf);

	return 0;
 //getHeaderOfFile
}


