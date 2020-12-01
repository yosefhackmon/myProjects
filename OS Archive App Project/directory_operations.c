/* directory_operations.c
 *
 * Yosef Hackmon
 * 
 * This File contains the main function for archiving a directory, but other types as well (in a recursive manner)
 * 
 *
 */

#include "main_operations.h"
//for debugging 
static int toTest = 0;
// printMode:
//	1 - print tree of directories and files
//	0 - the actual function! (creates the backup file)
static int printMode = 0; 

char *printPathLastElement(char *path){
	char nameBuf [SIZE_OF_NAME];
	char * retStr;

	memset(nameBuf, '\0', sizeof(nameBuf));
	strcpy(nameBuf, path);

	retStr = strrchr(nameBuf, '/');

	if(retStr == NULL){
	printf("retStr == NULL\n");
	}
	else{
	printf("retStr is: %s\n", retStr);
	}

	return retStr;

	
	
}
static int handle_archive_directory_tree_helper(int fd, char *pathname);

int partial_handle_archive_directory(char *pathname){
	//char *ptr = "directory";
	printf("%s [%s]\n", pathname, "directory");
	
	return 0;	
}
//it only write the data from the stat to the file .. 
//int partial_handle_archive_directory2(int fd, char *pathname){ //should be static
//params //
int partial_handle_archive_directory2(int fd, char *pAttrBuf){ //should be static
	try_write(fd, pAttrBuf, sizeof(file_attr_t));
	//instead of pathname i sent the pointer to the header! (we need to write it down!)
	
	
	//TODO
	return 0;
}



int  tester(){
	if(toTest){
	
	

	return 0;
	}

	return 0;
	
}

static int handle_archive_regular_file(char *pathname){

	printf("%s [%s]\n", pathname, "regular");

	return 0;
}
/*
int handle_archive_regular_file2(int fd, char *pathname){ //should be static
*/
//we send the buffer! pAttrBuf (and not the file pathname!)
int handle_archive_regular_file2(int fd, char *pAttrBuf){
	//file_attr_t attrBuf[sizeof(file_attr_t)];
	//file_attr_t *pfAttr = attrBuf;
	//write(fd, pfAttr, sizeof(file_attr_t))

	try_write(fd, pAttrBuf, sizeof(file_attr_t));
	
	//pfAttr->file_size = copyfileContent2(fd, path);
	copyfileContent2(fd, ((file_attr_t *)pAttrBuf)->name); //returns the amount of byte in the file! 
/*
	archive_regular_file(fd, pathname);
*/
	
	//TODO
	return 0;
}

static int handle_archive_symbolic_link(char *pathname){

	printf("%s [%s]\n", pathname, "symbolic link");

	return 0;
}
int handle_archive_symbolic_link2(int fd, char *pathname){// should be static

	INFO("ERROR: TODO - handle symbolic link! (need to implement). exiting ...\n");
	exit(1);
	
	//TODO
	return 0;
}



int findFileType (char* file_name){

	//int		i;
	struct stat	buf;
	char		*ptr;
	int retVal = 0;
	char cwd[SIZE_OF_NAME];
	//for (i = 1; i < argc; i++) {
		//printf("%s: ", file_name);

		printf("in other_operations: func getFileType: file_name is %s\n", file_name);

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
		printf("in other_operations: func getFileType(), lstat finish gracefullY: file_name is %s\n", file_name);
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


static int print_directory_tree_helper(char *pathname){
	//int  fdToDo = -1;
	int retVal;
	char *ptr;

	struct stat buf;
	char fAttrBuf[sizeof(file_attr_t)];
	
	//ssize_t noBytesWritten;
	file_attr_t *pfAttr;
	pfAttr = (file_attr_t *)fAttrBuf;
	

	char path_of_content[SIZE_OF_NAME];
	char *newPath = path_of_content;

	memset(path_of_content, '0', sizeof(path_of_content));

	if(pfAttr){ tester(); }


	//already include an lstat .. 
	getHeaderFromFile(pathname, fAttrBuf); //here we can return a string or a value .. 
	

	try_lstat(pathname, &buf);
	
	if      (S_ISREG(buf.st_mode))	{ptr = "regular"; retVal=1;}
	else if (S_ISDIR(buf.st_mode))	{ptr = "directory"; retVal=2;}
	else if (S_ISLNK(buf.st_mode))	{ptr = "symbolic link"; retVal=3;}
	else {			ptr = "** unknown mode **"; retVal = 0;}

	if(!retVal){ //retVal ==0 , unknown mode (i.e. unknown file type)
		INFO(ptr);
		exit(1);
		}
	//TODO now we know! what to do in case .. each of the cases .. 
	//choose if to write the header now! 

	//here we choose action - if it is a file ..
		//write header
		//copycontent .. 
		//write to a regular file .. 

	
	printf("%s [%s]\n", pathname, ptr);

	if(retVal == 1) { //this is a regular file
		
		handle_archive_regular_file(pathname);
		//handle_archive_regular_file2(fd, pathname);
	return 0;
	}


	if(retVal == 3) {//this is a sym_link
		
		handle_archive_symbolic_link(pathname);
		//handle_archive_symbolic_link2(fd, pathname);		

		return 0;
	}

	if(retVal != 2)  //not needed
		return 0;

	
	//else ..
	//handle_archive_directory(fd, pathname); //not needed! 
	DIR *dir;
	struct dirent *sd;

	//printf("***** in handleDirContent(char *path = %s, name is: pfAttr->name: %s *****\n", path, pfAttr->name);
	/* TODO replace "." with the directory the file should be in*/
	dir = opendir(pathname); //open current working directory
	
	if(dir == NULL){
		printf("ERROR: in %s: Unable to open directory. exiting ...\n", __FUNCTION__);
		exit(1);
	}

	while((sd = readdir(dir)) != NULL){
		/*
		if((strcmp(fileName, sd->d_name)) == 0){
			res = 1;
			break;
		}
		*/
	//FiX:
	//file_name = sd->d_name;

	//if(sd->d_name == 0)
	//create the new path name..
	strcpy(newPath, pathname);
	strcat(newPath, "/");
	strcat(newPath, sd->d_name);
	
	if(strcmp(sd->d_name, ".") == 0 ||  strcmp(sd->d_name, "..") == 0){

		//we are not foint to save them! 
		printf("%s [%s]\n", newPath, ptr);
	} else {

	//printf("%s [%s]\n", newPath, ptr);
	print_directory_tree(newPath);
	}
	//findFileType(pathname);
	}//while
	return 0;
	
}

int print_directory_tree(char *pathname){

	print_directory_tree_helper(pathname);

	return 0;
}
/*
static int handle_archive_directory_tree_helper(int fd, char *pathname){
	
	//TODO
	return 0;
}
*/
//we will create a function .. that tells us 
int handle_archive_directory_tree(int fd, char *pathname){
	
	if(fd < 0){
		INFO("TODO: pass fd to handle_archive_directory_tree_helper\n");
		exit(1);
	}
	handle_archive_directory_tree_helper(fd, pathname);
	return 0;
}

//as we just saw.. we don't leave the zone we are in .. 


static int handle_archive_directory_tree_helper(int fd, char *pathname){
	//int  fdToDo = -1;
	int retVal;
	char *ptr;

	struct stat buf;
	char fAttrBuf[sizeof(file_attr_t)];
	
	//ssize_t noBytesWritten;
	file_attr_t *pfAttr;
	pfAttr = (file_attr_t *)fAttrBuf;
	

	char path_of_content[SIZE_OF_NAME];
	char *newPath = path_of_content;

	memset(path_of_content, '0', sizeof(path_of_content));

	if(pfAttr){ tester(); } //TODO Line is not needed


	//already include an lstat .. 
	getHeaderFromFile(pathname, fAttrBuf); //here we can return a string or a value .. 
	

	try_lstat(pathname, &buf);
		
	if      (S_ISREG(buf.st_mode))	{ptr = "regular"; retVal=1;}
	else if (S_ISDIR(buf.st_mode))	{ptr = "directory"; retVal=2;}
	else if (S_ISLNK(buf.st_mode))	{ptr = "symbolic link"; retVal=3;}
	else {			ptr = "** unknown mode **"; retVal = 0;}

	if(retVal == 0){ //retVal ==0 , unknown mode (i.e. unknown file type)
		if(ptr){printf("ptr == %s\n", ptr);} //TODO Line is not needed
		
		INFO("ERROR: ptr is ** unknown mode **. exiting ...\n");
		exit(1);
		}
	//TODO now we know! what to do in case .. each of the cases .. 
	//choose if to write the header now! 

	//here we choose action - if it is a file ..
		//write header
		//copycontent .. 
		//write to a regular file .. 

	
	//printf("%s [%s]\n", pathname, ptr); //TODO replace that with writing the buffer into fd;

	else if(retVal == 1) { //this is a regular file
	if(printMode){
		handle_archive_regular_file(pathname);
	} else {
		//handle_archive_regular_file(pathname);
		//handle_archive_regular_file2(fd, pathname);
		handle_archive_regular_file2(fd,(char *) pfAttr);
	}
	return 0;
	}


	else if(retVal == 3) {//this is a sym_link
		if(printMode){
		handle_archive_symbolic_link(pathname);
		} else {
		handle_archive_symbolic_link2(fd, pathname);		
		}
		return 0;
	} //else: ... 

	//if(retVal != 2)  //not needed
	//	return 0;
	if(retVal == 2){ //partialy_handle: we write buffer 

	//here we just write things into the file into fd!
	if(printMode){
	partial_handle_archive_directory(pathname); //This is prints
	} else {
	partial_handle_archive_directory2(fd, (char *)pfAttr);
	}
	//printf("%s [%s]\n", pathname, ptr);
	}

	//else ..
	//handle_archive_directory(fd, pathname); //not needed! 
	DIR *dir;
	struct dirent *sd;

	
	/* TODO replace "." with the directory the file should be in*/
	dir = opendir(pathname); //open current working directory
	
	if(dir == NULL){
		printf("ERROR: in %s: Unable to open directory. exiting ...\n", __FUNCTION__);
		exit(1);
	}

	while((sd = readdir(dir)) != NULL){
		/*
		if((strcmp(fileName, sd->d_name)) == 0){
			res = 1;
			break;
		}
		*/
	//FiX:
	//file_name = sd->d_name;

	//if(sd->d_name == 0)
	//create the new path name..
	strcpy(newPath, pathname);
	strcat(newPath, "/");
	strcat(newPath, sd->d_name);
	
	//printPathLastElement(newPath);

	if(strcmp(sd->d_name, ".") == 0 ||  strcmp(sd->d_name, "..") == 0){
		//we are not foint to save them! 
		//printf("%s [%s] This is Dot or 2-Dots\n", newPath, ptr);
	} else {

	//printf("%s [%s]\n", newPath, ptr);
	//print_directory_hand(newPath);
	handle_archive_directory_tree_helper(fd, newPath);
	}
	//findFileType(pathname);
	}//while
	return 0;
}
