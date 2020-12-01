 
/* extract_tree.c
 * 
 * Yosef Hackmon
 *
 * This file contains the actual function for extracting the data out of a backup-file, created earlier with the program: mkbkp
 *   
 * 
 *
 */
#include "main_operations.h"
#define INFO_ARGS __FILE__, __LINE__, __FUNCTION__
/*
 * getHeaderFromBackupFile(int fd, char *pAttrBuf, size_
 */
//int getHeaderFromBackupFile(char *path, char *fAttrBuf){

//given an open fd, we are taking up to: sizeOfHeader
//we take a chunk of the header and put it in the fAttrBuf
int getHeaderFromBackupFile(int fd, char *pAttrBuf){

	


	return 0;
}


int my_do_extract2 (int fd, long long numBytesToRead){
	//TODO	

	//int fd;
	struct utimbuf  times;
	file_attr_t fAttr, *pfAttr;
	char fAttrBuf[sizeof(fAttr)];
	ssize_t noBytesRead;
	
	long long newNumBytesToRead;

//	long long regFileSizeInBytes;
	//struct stat buf;	

	//open the file, test if it is regular, dir, symlink .. 
	/*if((fd = open(backup_file, O_RDONLY)) < 0){
		fprintf(stdout,"open error for file: %s, exiting ...",backup_file);
		exit(1);
	}*/
	
	pfAttr = (file_attr_t *)fAttrBuf;
	//pfAttr = fAttrBuf;
	//printf("sizeof(pfAttr)==%d\n", sizeof(pfAttr));
	memset(pfAttr, 0, sizeof(fAttr)); //the size of an header  // not needed! 

	//postcondition: noBytesRead have to be equal to sizeof(file_attr_t)
	if((noBytesRead =  read(fd, pfAttr, sizeof(file_attr_t))) < 0){
		fprintf(stderr,"read error\n");
		exit(1);
		}

	if(noBytesRead != sizeof(file_attr_t)){
		INFO("ERROR: read less then sizeof(file_attr_t) bytes! exiting ...\n");
		exit(1);
	}

	newNumBytesToRead = numBytesToRead - noBytesRead;
	
	//now we can extract all the data that we need! 
	//the name ..
	//the size .. (without the header)! 
	//the type ..
	//printf("\n in extract\n\n");
	
	//printFAttr(pfAttr);
	//print_extract_treint fd, 

//	handle_extract_tree(fd,(char *)pfAttr);
	
	//now we should read the data, let's try it ..  
	//we need a char buf for the 

	//here we open the file and test that this is ours, the size must be at least as header! 
	//TODO here we should make some check! 
	if((strcmp(pfAttr->type, "regular")) == 0){
	
	//	if(
		//try_extract_regular_file(
		extract_regular_file(fd, pfAttr);
		newNumBytesToRead -= pfAttr->st_size;
	
		if(newNumBytesToRead == 0){
			return 0;
	}
		my_do_extract2(fd, newNumBytesToRead);

	} else if ((strcmp(pfAttr->type, "directory")) == 0){
		//my_extract_directory2(fd, pfAttr);
		//printf("the mode is: pAttrBuf->st_mode: %lo\n", ((file_attr_t *)pfAttr)->st_mode); 
	
		try_mkdir(((file_attr_t *)pfAttr)->name,((file_attr_t *)pfAttr)->st_mode); 
		
		
		
		try_lchown(pfAttr->name, pfAttr->st_uid, pfAttr->st_gid);
		
		times.actime = pfAttr->atime;
		times.modtime = pfAttr->mtime;
		try_utime(pfAttr->name, &times);

		if(newNumBytesToRead == 0){
			return 0;
		}
		
		my_do_extract2(fd, newNumBytesToRead);
		
	} else if ((strcmp(pfAttr->type, "symbolic link")) == 0){
		//extract_symbolic_link(fd, pfAttr);
		INFO("ERROR: can't handle extract symbolic link yet! exiting ...\n");
		exit(1);
	} else {
		printf("ERROR: in do_extract: can't recognize the file type, exiting ...\n");
		exit(1);
	}

	
	
	//extract_regular_file(backup_file);
/*
	if((close(fd)) < 0){
		fprintf(stdout, "close error for a file, exiting ... \n");
		exit(1);
	}
	*/
	return 0;
}
//we get an open fd and then we can tell .. 

//int handle_extract_tree_helper(int fd, char *pAttrBuf, long long numBytesToRead){
/*
int handle_extract_tree_helper(int fd,  long long numBytesToRead){

	
	file_attr_t fAttr, *pfAttr;
	char fAttrBuf[sizeof(fAttr)];
	ssize_t noBytesRead;

	pfAttr = (file_attr_t *)fAttrBuf;
	//pfAttr = fAttrBuf;
	printf("sizeof(pfAttr)==%d\n", sizeof(pfAttr));
	memset(pfAttr, 0, sizeof(fAttr)); //the size of an header  // not needed! 

	//postcondition: noBytesRead have to be equal to sizeof(file_attr_t)
	if((noBytesRead =  read(fd, pfAttr, sizeof(file_attr_t))) < 0){
		fprintf(stderr,"read error\n");
		exit(1);
		}
	//we start with fd .. 

}
*/
//here - i came from a .. folder, so the header, if exist .. is of another folder..
/*
int handle_extract_tree_helper(int fd, char *pAttrBuf, long long numBytesToRead){
	long long fd_st_size;
	struct stat buf;
	if((fstat(fd, &buf))<0){
		INFO("fstat fail! exiting ...\n");
		exit(1);
	}

	fd_st_size = buf.st_size; //lstat of the backup file!!! 
	printf("fd_st_Size == %lld\n", fd_st_size);
	//what mode should we choode? 
	printf("the mode is: pAttrBuf->st_mode: %lo\n", ((file_attr_t *)pAttrBuf)->st_mode); //this is the mode we need to reserve! 
	try_mkdir(((file_attr_t *)pAttrBuf)->name,((file_attr_t *)pAttrBuf)->st_mode);

	
	fd_st_size -= sizeof(file_attr_t);
	printf("sizeof(file_attr_t) == %d\n", sizeof(file_attr_t));
	printf("fd_st_Size - sizeof(file_attr_t) == %lld\n", fd_st_size);
	
	//printf("after mk dir\nexit ...\n");
	//fflush(stdout);

	
	// here we shouold do this over and over ...
	return 0;
}
*/
/*
int handle_extract_tree(int fd, char *pAttrBuf){

	//if((file_attr_t *)pAttrBuf)->type
	long long fd_st_size; //the size left in the file .. (if it is 0 ..  and pAttrBuf->type is file, and number of bytes in the file .. 
			//	we then create new empty fle with name .. 
	
	struct stat buf;
	if((fstat(fd, &buf))<0){
		INFO("fstat fail! exiting ...\n");
		exit(1);
	}

	fd_st_size = buf.st_size; //sizeOfThe fd!! 
	printf("fd_st_Size == %lld\n", fd_st_size);
	//what mode should we choode? 
	printf("the mode is: pAttrBuf->st_mode: %lo\n", ((file_attr_t *)pAttrBuf)->st_mode); //this is the mode we need to reserve! 
	try_mkdir(((file_attr_t *)pAttrBuf)->name,((file_attr_t *)pAttrBuf)->st_mode); 

	fd_st_size -= sizeof(file_attr_t);
	
	printf("sizeof(file_attr_t) == %d\n", sizeof(file_attr_t));
	printf("fd_st_Size - sizeof(file_attr_t) == %lld\n", fd_st_size);
	
	//printf("after mk dir\nexit ...\n");
	//fflush(stdout);
	printf("%s:%d: in %s:  fd_st_size == %lld. continue the function..\n", INFO_ARGS, fd_st_size);
	if(fd_st_size < 0){
		printf("%s:%d: in %s: ERROR: fd_st_size < 0 !! exiting .. \n", INFO_ARGS);
		exit(1);
		} 
	here we shouold do this over and over ... 
	return 0;
}
*/
int my_do_extract1(int fd){

	//if((file_attr_t *)pAttrBuf)->type
	long long fd_st_size; //the size left in the file .. (if it is 0 ..  and pAttrBuf->type is file, and number of bytes in the file .. 
			//	we then create new empty fle with name .. 
	
	struct stat buf;
	if((fstat(fd, &buf))<0){
		INFO("fstat fail! exiting ...\n");
		exit(1);
	}

	fd_st_size = buf.st_size; //sizeOfThe fd!! 
	printf("fd_st_Size == %lld\n", fd_st_size);


	my_do_extract2(fd, fd_st_size);
	return 0;
	/*
	//what mode should we choode? 
	printf("the mode is: pAttrBuf->st_mode: %lo\n", ((file_attr_t *)pAttrBuf)->st_mode); //this is the mode we need to reserve! 
	try_mkdir(((file_attr_t *)pAttrBuf)->name,((file_attr_t *)pAttrBuf)->st_mode); 

	fd_st_size -= sizeof(file_attr_t);
	
	printf("sizeof(file_attr_t) == %d\n", sizeof(file_attr_t));
	printf("fd_st_Size - sizeof(file_attr_t) == %lld\n", fd_st_size);
	
	//printf("after mk dir\nexit ...\n");
	//fflush(stdout);
	printf("%s:%d: in %s:  fd_st_size == %lld. continue the function..\n", INFO_ARGS, fd_st_size);
	if(fd_st_size < 0){
		printf("%s:%d: in %s: ERROR: fd_st_size < 0 !! exiting .. \n", INFO_ARGS);
		exit(1);
		}
*/ 
	
	return 0;
}



