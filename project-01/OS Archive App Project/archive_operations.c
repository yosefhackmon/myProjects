/* archive_operations.c */
/*
#include	<sys/types.h>
#include	<sys/stat.h>
#include        <stdio.h>
*/
//#include "mkbkp.h"
#include	"main_operations.h"
static int test = 1;
static int oldVersion = 0;

static int printReason(int err_num){

 char *msg1 = "Search  permission  is  denied for one of the directories in the  path prefix of path." ;
 char *msg2 =  "fd is bad.";
char *msg3 = "Too many symbolic links encountered while traversing the path.";
 char *msg4 = "path is too long.";
char *msg5 = "A component of path does not exist, or path is an empty string.";
char *msg6 = "Out of memory ";
 char *msg7 =   "A component of the path prefix of path is not a directory.";
 char *msg8 =    "Bad address.";

printf("Reason: ");

	switch(err_num){
case EACCES:
 printf("%s\n", msg1); break;

case EBADF: 
printf("%s\n", msg2); break;
      
case EFAULT: printf("%s\n", msg8); break;

case  ELOOP: printf("%s\n", msg3); break;

case ENAMETOOLONG:
	printf("%s\n", msg4); break;
   
case ENOENT:
	printf("%s\n", msg5); break;

 case ENOMEM :
printf("%s\n", msg6); break;


case  ENOTDIR:
printf("%s\n", msg7); break;

default:
printf("other\n");
}

return 0;
}


//A recursive function
/*
 * do_archive parameters:
 * fd -  an open file ready to be written to, where to put the data in (the backup)
 * and then the *path - the object to be archived (inside fd)
 *
 *
 *
*/

//this function suppose to write down to handle with the object inside .. the dir! 

/*
 * we start in ~/workspace/mydfs <= we are here
 * we get the Folder3 (the folder to be archived) in the path! 
 * so the path will be Folder3
 * we enter: ** chdir(Folder3) **
 * current working directory: 	(~/workspace/mydfs/)Folder3/ <= assume .. 
 * now we opendir("."); //to examine the file reside in Folder3/ 
 * now we take file by file: from the stream  **readdir(dir) ** (while readdir != null .. we have what to read in the directory/)
 *
 * we are inside Folder3 so we are not changing the pathname (yet! ) => the longpath name will be used later ..
 * we are going to put it inside the name member of the file_attr_t..
 *
 * once we check ..
 * before we send the file to start on its own .. we change dir .. "up" current working directory. and after it is finish .. we take the current dir down again! 
 *
*/

int handle_dir_contents2(int fd, char *path){
	
	int functionVersion = 2;
	DIR *dir;
	struct dirent *sd;
	char newPath[SIZE_OF_NAME]; 
	char *subDirPath;
	char *regFilePath;
	char *file_name;
	int fTypeNum = 0;

	char cwd[SIZE_OF_NAME];


	printf("START function: %s\n", __FUNCTION__);


	//char *symLinkPath;
	memset(newPath, '0', sizeof(newPath));
	memset(cwd, '0', sizeof(cwd));

	printf("\n **** in handle_dir_contents%d (int fd := %d, char *path := %s) **** \n", functionVersion , fd, path);

	getcwd(cwd, sizeof(cwd));
	//printf( "begin: handle_dir_contents, BEFORE chdir	cwd == %s\n", cwd);

//	printf("in archive_operations.c: func handle_dir_contents(path [before change] = %s)\n", path);
	if(oldVersion){
	if((chdir(path)) < 0){
		printf("ERROR: chdir(%s) failed. exiting..\n", path);
		exit(1);
	}
	
	getcwd(cwd, sizeof(cwd));
	printf( "in handle_dir_contents%d, AFTER chdir	cwd == %s\n",functionVersion, cwd);
		
	//we are in path! 
	// TODO replace "." with the directory the file should be in
	dir = opendir("."); //open current working directory
	} else {
	
		//CHANGE DIR: in order to exemine the content of (the data) inside the directory.
		if((chdir(path)) < 0){
		printf("ERROR: -1- chdir(%s) failed. exiting..\n", path);
		exit(1);
		}
		
		//getcwd(cwd, sizeof(cwd));
		//printf( "in handle_dir_contents, AFTER chdir	cwd == %s\n", cwd);

		dir = opendir(".");
	}

	//printf("in archive_operations.c: func handle_dir_contents(path [before change] = %s)\n", path);

	if(dir == NULL){
		INFO("handle_dir_contents2, Unable to open directory!");
		printf("ERROR: (): Unable to open directory. exiting ...\n");
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
	fTypeNum = getFileType(file_name);

	if(fTypeNum == 0){
		printf("ERROR: -2- in handle_dir_contents(), file type is unfamiliar, can't archive. exiting ..\n");
		exit(1);
	}

	if(fTypeNum == 1 || (fTypeNum == 2 && strcmp(file_name, "..") && strcmp(file_name, "."))){
	
	//subDirPath = newPath;
	//memset(newPath, '0', sizeof(newPath));
		
		//this the path we get .. releative to our begining 
		strcpy(newPath, path);
		strcat(newPath, "/");
		strcat(newPath, sd->d_name);

	
	}
	
	
	
	if((chdir(cwd)) < 0){
		printf("im here\n");
		printf("ERROR: -3- chdir(%s) failed. exiting..\n", cwd);
		exit(1);
	}

	//this is a directory and not current dir or previous one, need to call recursively to
	if(fTypeNum == 2 && strcmp(sd->d_name, ".") && strcmp(sd->d_name, "..")){
		//path is up until the current directory .. 
		//concat: path + '/' + sd->d_name;
			subDirPath = newPath;
			/*
			memset(subDirPath, '0', sizeOf(newPath);
			
			strcpy(subDirPath, path);
			strcat(subDirPath, '/');
			strcat(subDirPath, sd->d_name);		
			*/
			printf("subDirPath: == %s\n" , subDirPath);
			
			//here we should change the working dir .. 
			/*
			if((chdir(cwd)) < 0){
				printf("ERROR: chdir(%s) failed. exiting..\n", path);
				exit(1);
			*/
			archive_directory(fd, subDirPath);
			/*
			if((chdir(path)) < 0){
				printf("ERROR: chdir(%s) failed. exiting..\n", path);
				exit(1);
			//when we finish we are going back one Level up
			*/	
	} else if (fTypeNum == 1) {
		//printf("condition sd->dname: %s != \".\"\n", sd->d_name);
		//its a regular file:
		
		regFilePath = newPath;
		printf("regFilePath: == %s\n" , regFilePath);

		archive_regular_file(fd, regFilePath);
		
	} else if(fTypeNum == 3){
		printf("\n***** TODO ****\nHandle symlink, in function: handle_dir_contents! exiting ...\n");
		exit(1);
		}


	//printf("current Workin
	//if((chdir(path)) < 0){
	if((chdir("..")) < 0){
		printError(errno);
		INFO("chdir failed!\n");
		printf("ERROR: chdir -4- (%s) failed. exiting..\n", path);
		exit(1);
	}
/*	//count++;
	
	
	switch(fTypeNum){
	case 3: //doNothingFornow
		break;
	case 2: 
		break;
	case 1: pfAttr->noRegFile++;
		break;
	case 0: printf("in handleDirContent: Error - unknown file type (getFileType(%s) == 0). exiting ..\n", file_name);
	default: exit(1);

	}
	
*/
	}

	/** TODO print! **/

	printf("IM HERE -5-: handle_dir_contents2: path is %s\n", path);
	
 
	if((closedir(dir)) <0){
		printf("ERROR in regular_file_already_exist(): Unable to close directory. exiting ...\n");
		exit(1);
	}	

	return 1;
}

/*
int handle_dir_contents(int fd, char *path){

	
	DIR *dir;
	struct dirent *sd;
	char newPath[SIZE_OF_NAME]; 
	char *subDirPath;
	char *regFilePath;
	char *file_name;
	int fTypeNum = 0;
	char cwd[SIZE_OF_NAME];
	//char *symLinkPath;
	memset(newPath, '0', sizeof(newPath));
	memset(cwd, '0', sizeof(cwd));

	printf("\n **** in handle_dir_contents(int fd := %d, char *path := %s) **** \n", fd, path);

	getcwd(cwd, sizeof(cwd));
	printf( "begin: handle_dir_contents, BEFORE chdir	cwd == %s\n", cwd);

//	printf("in archive_operations.c: func handle_dir_contents(path [before change] = %s)\n", path);
	if(oldVersion){
	if((chdir(path)) < 0){
		printf("ERROR: chdir(%s) failed. exiting..\n", path);
		exit(1);
	}
	
	getcwd(cwd, sizeof(cwd));
	printf( "in handle_dir_contents, AFTER chdir	cwd == %s\n", cwd);
		
	//we are in path! 
	// TODO replace "." with the directory the file should be in
	dir = opendir("."); //open current working directory
	} else {
	
		if((chdir(path)) < 0){
		printf("ERROR: chdir(%s) failed. exiting..\n", path);
		exit(1);
	}

		getcwd(cwd, sizeof(cwd));
		printf( "in handle_dir_contents, AFTER chdir	cwd == %s\n", cwd);

		dir = opendir(path);
	}

	printf("in archive_operations.c: func handle_dir_contents(path [before change] = %s)\n", path);

	if(dir == NULL){
		printf("ERROR: in regular_file_already_exist(): Unable to open directory. exiting ...\n");
		exit(1);
	}

	while((sd = readdir(dir)) != NULL){
		
	
	file_name = sd->d_name;
	fTypeNum = getFileType(file_name);

	if(fTypeNum == 0){
		printf("ERROR: in handle_dir_contents(), file type is unfamiliar, can't archive. exiting ..\n");
		exit(1);
	}

	if(fTypeNum == 1 || fTypeNum == 2){
	
	//subDirPath = newPath;
	//memset(newPath, '0', sizeof(newPath));
			
		strcpy(newPath, path);
		strcat(newPath, "/");
		strcat(newPath, sd->d_name);

	
	}
	
	//this is a directory and not current dir or previous one, need to call recursively to
	if(fTypeNum == 2 && strcmp(sd->d_name, ".") && strcmp(sd->d_name, "..")){
		//path is up until the current directory .. 
		//concat: path + '/' + sd->d_name;
			subDirPath = newPath;
			
			printf("subDirPath: == %s\n" , subDirPath);
			archive_directory(fd, subDirPath);
			
			//when we finish we are going back one Level up
		
	} else if (fTypeNum == 1) {
		//printf("condition sd->dname: %s != \".\"\n", sd->d_name);
		//its a regular file:
		
		regFilePath = newPath;
		printf("regFilePath: == %s\n" , regFilePath);

		archive_regular_file(fd, regFilePath);
		
	}
	

	if(fTypeNum == 3){
		printf("\n***** TODO ****\nHandle symlink, in function: handle_dir_contents! exiting ...\n");
		exit(1);
		}

	}

	
	if((closedir(dir)) <0){
		printf("ERROR in regular_file_already_exist(): Unable to close directory. exiting ...\n");
		exit(1);
	}	

	return 1;
}
*/

//we suppose both files are open and we can just read from

long long handleDirContent(char *path, file_attr_t * pfAttr ){
	
	

	long long  res = 0;
	int fTypeNum;
	long count = 0;
	char *file_name;
	//path_of_content := path(of dir) concatenated with the chosen file/directory from the current dir
	char path_of_content[SIZE_OF_NAME];
	char *newPath = path_of_content;
	memset(path_of_content, '0', sizeof(path_of_content));

	DIR *dir;
	struct dirent *sd;

	//printf("***** in handleDirContent(char *path = %s, name is: pfAttr->name: %s *****\n", path, pfAttr->name);
	/* TODO replace "." with the directory the file should be in*/
	dir = opendir(path); //open current working directory
	
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
		
	file_name = sd->d_name;

	strcpy(newPath, path);
	strcat(newPath, "/");
	strcat(newPath, sd->d_name);

	

	count++;
	printf("here\n");
	//fTypeNum = getFileType(file_name);
	fTypeNum = getFileType(path_of_content);
	switch(fTypeNum){
	case 3: pfAttr->noSymLink++;
		break;
	case 2: pfAttr->noSubDir++;
		break;
	case 1: pfAttr->noRegFile++;
		break;
	case 0: printf("in handleDirContent: Error - unknown file type (getFileType(%s) == 0). exiting ..\n", file_name);
	default: exit(1);

	}
	
	
	}

	if((closedir(dir)) <0){
		printf("ERROR in regular_file_already_exist(): Unable to close directory. exiting ...\n");
		exit(1);
	}	
	res += pfAttr->noSymLink;
	res += pfAttr->noSubDir;
	res += pfAttr->noRegFile;
	//return pfAttr->noSymLink + pfAttr->noSubDir + pfAttr->noRegFile;

	printf("noSymLink: %ld\n", pfAttr->noSymLink);
	printf("noSubDir: %ld\n", pfAttr->noSubDir);
	printf("noRegFile: %ld\n", pfAttr->noRegFile);

	return res;
}

static int  copyfileContent(int fd_to_be_written, char *path){
	//todo change the mask to feet the right one! 
	
	char buf;
	int readRetVal;
	int writeRetVal;

	int fd1; 
	//ssize_t count;
	int counter = 0; //count how many bytes read so far
	// umask( S_IWGRP | S_IWOTH);
	// if ((fd = open(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
		if( (fd1 = open(path, O_RDONLY)) < 0){
                fprintf(stdout,"open error for file: %s",path);
		exit(1);
		}
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
 int archive_directory (int fd, char *path){
	//TODO
	char fAttrBuf[sizeof(file_attr_t)];
	ssize_t noBytesWritten;
	file_attr_t *pfAttr;

	pfAttr = (file_attr_t *)fAttrBuf;
	/*
	struct stat	buf;
	//char		*ptr = filetype(path);
	
	if (lstat(path, &buf) < 0) {
			fprintf(stderr,"lstat error");
			exit(1);
		}
	*/
	getHeaderFromFile(path, fAttrBuf);
	//printf("*** 1 ***\n");
	printFAttr((file_attr_t*)fAttrBuf);

	//long long  handleDirContent(char *path, file_attr_t * pfAttr);

	//handleDirHeader
	handleDirContent(path, pfAttr);
	//getDirectorySpecialInfo();
	//int handleDirContent(char *
	//printf("*** 2 ***\n");
	//printFAttr(pfAttr);
	//write the header! 
	if((noBytesWritten =  write(fd, pfAttr, sizeof(file_attr_t))) < 0){
		fprintf(stderr,"write error");
		exit(1);
		}
	//res += pfAttr->noSymLink;
	//res += pfAttr->noSubDir;
	/* if(pfAttr->noRegFile > 0){
		Archive_regular_of_dir()

	if(pfAttr->noSymLink > 0) {
		Archive_regular
	*/

	//condition to stop the recursion
	//if(pfAttr->noRegFile == 0 && pfAttr->noSymLink == 0 && pfAttr->noSubDir ==2){
	if(pfAttr->noRegFile == 0 && pfAttr->noSubDir ==2){
		
		if(pfAttr->noSymLink != 0)
			printf("pfAttr->noSymLink == %ld\n", pfAttr->noSymLink);

		return 0;
	}
	

	handle_dir_contents2(fd, path);
	//if(pfAttr->No
	return 0;
	
}

//so fd is now open!
//path is basically the file we want to back up
/* we are going to:
 * copy the file attributes to fd
 * copy the file content to fd (just after!)
 *
 *
 */
 int archive_regular_file (int fd, char *path){
	//TODO
	//assume fd is now open! 
	// path is a regular file!
	//size_t count = sizeof(struct stat);
	file_attr_t fAttr, *pfAttr;
	char fAttrBuf[sizeof(fAttr)];
	ssize_t noBytesWritten;
	//the file is open! 
	struct stat	buf;

	char header[SIZE_OF_FILE_HEADER];
	
	//char		*ptr = filetype(path);
	if (lstat(path, &buf) < 0) {
			fprintf(stderr,"lstat error");
			exit(1);
		}
	
	//we use pfAttr as a pointer to charbuf 
	pfAttr = (file_attr_t *)fAttrBuf;
	memset(header, 0, SIZE_OF_FILE_HEADER); //not needed 
	memset(pfAttr, 0, sizeof(fAttr)); //the size of an header 

	
	 
	memcpy(pfAttr->name, path, strlen(path)); //copy from the path into the buffer .. 

	memcpy(pfAttr->type, "regular", strlen("regular"));

	memcpy(pfAttr->magic_name, "mkbkp", strlen("mkbkp"));

		//write the buf (struct stat) info into the file ..
		pfAttr->file_size = buf.st_size;
	
	//string operations to copy the content 
	getStatAttr(pfAttr, &buf);
	
	//printf(

	/*  fill in the buffer-header with correct data! */
	//assume: file_name_offset in header is 0
		//premission bits mode offset is in offset 64

		//
/*
	if((noBytesWritten =  write(fd, &header, SIZE_OF_FILE_HEADER)) < 0){
		fprintf(stderr,"write error");
		exit(1);
		}
*/
	//write down to the header .. 
	if((noBytesWritten =  write(fd, pfAttr, sizeof(file_attr_t))) < 0){
		fprintf(stderr,"write error");
		exit(1);
		}

	//copy the content .. line by line? 
	//return the size of the file (how many head beed read..)
	if(test == 1){
		//copyFileContent2: this is for regular files; //HANDLE REGULAR FILE CONTENT
		pfAttr->file_size = copyfileContent2(fd, path);
	} else {

	pfAttr->file_size = copyfileContent(fd, path); //copy the contents of the the file given by path to the already opened file given as fd	
	}
	//write(fd, &(pfAttr->file_size), sizeof(long long));
	
	printf("pfAttr->file_size: %lld\n", pfAttr->file_size);
	
	return fd;
}

//we have the function filetype which returns the filetype, as a pointer to some static string
int do_archive (char *backup_file, char *path){

	/* copy the fileToArchive stat into buf*/
	int err_num;
	int fd = 0;
	struct stat	buf;
	//char		*ptr = filetype(path);
	char* ptr;
	char buf_path[SIZE_OF_NAME];
	if (lstat(path, &buf) < 0) {
			err_num = errno;
			
			fprintf(stderr,"lstat error: can't archive, exiting ...\n");
			printReason(err_num);
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
//#ifdef	S_ISSOCK
//		else if (S_ISSOCK(buf.st_mode))	ptr = "socket";
//#endif
		else				ptr = "** unknown mode **";

		
	//if we are here that we can try to open the backup_file (for few reasons!) //maybe we shpuld open it from the main!

	//TODO we might open the file backup_file here!

//	printf("%s\n", ptr);	
	
	//open The file in backup_file 
	//if the file backup_file is already exist - we override it! //backup_file is a string! 
	unlink(backup_file); //if the file is was linked earlier - we realease it - DEANGEROUS!!

	
	//we create a file with: -rw-r--r-- permissions

	// umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	// USE O_APPEND
	//

	
	//test this one
	if(!strcmp(ptr, "regular")){
	
	 umask( S_IWGRP | S_IWOTH);
	 if ((fd = creat(backup_file, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
                fprintf(stdout,"creat error for backup_file: %s", backup_file);

	//backupfile is always in the current directory! 
	//fd = open(backup_file,

	archive_regular_file(fd, path);

	if((close(fd)) < 0){
		printf("ERROR: unable to close open file. exiting ...\n");
		exit(1);
			}
	return 0;
	}
	
		


	if(!strcmp(ptr,"directory")){
	
		//create new file to save the data of the directory inside
		 umask( S_IWGRP | S_IWOTH);
		 if ((fd = creat(backup_file, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
             		   fprintf(stdout,"creat error for backup_file: %s", backup_file);

		//fd = createFileForDirectoryBackup(backup_file);
		//archive_directory(fd, path);
		delete_the_trailing_slash_if_exist(path, buf_path, sizeof(buf_path));
		handle_archive_directory_tree(fd, buf_path);

		//archive_directory_tree(fd, path);
		if((close(fd)) < 0){
			printf("ERROR: unable to close open file. exiting ...\n");
			exit(1);
			}
		return 0;

	}
	//TODO
	return 0;
}

/*
static int archive_directory (char *backup_file, char *path){
	//TODO
	return 0;
}

static int archive_regular_file (char *backup_file, char *path){
	//TODO
	return 0;
}
*/
/*
static int archive_symbolic_link (char *backup_file, char *path){
	//TODO
	return 0;
}
*/


