/* string-operations.c 
 *
 *
 *  Yosef Hackmon 
 * 
 * This File provide functions that help us maintain the pathname of the file and directories in a fixed manner
 * 
 * 
 * 
 */

int  create_the_missing_path(char *pathname);

#include "main_operations.h"

//TODO change the mode of mkdir! 
 static mode_t mkdir_mode = 0755;

//TODO handle this counter (not needed!)
int counter = 5;

#define TESTMODE 1 
#define REALMODE 0
//TODO remove this one.
static int shouldPrint = 0;
static int testMode = TESTMODE; //i.e. we should test //if testMode = 1 then we need to use the counter.. 
//static int realMode = REALMODE;
//static int realMode = !testMode; // 

	//&& (realMode || tcounter>0 )
//if(shouldPrint){



int make_dir_if_not_exist(char *buf){
	DIR *dir;
	if(shouldPrint){
	printf("int %s: buf is == %s\n", __FUNCTION__, buf);
	}
	if ((dir = opendir(buf)) == NULL){
		if(shouldPrint){
		INFO("(dir = opendir(buf)) == NULL\n");
		}
		if(errno == ENOENT){
			if(shouldPrint){
			INFO("making dir .. \n");
			}
			try_mkdir(buf,mkdir_mode);
			}
		else { //opendir() == NULL && errno != ENOENT => 
			INFO("create_the_missing_path: opendir failed! exiting ..\n");
			exit(1);
			
		 }
	} else { 
		try_closedir(dir); 
	}

	return 0;
}

/* 
 * This functions is called in case we want to extract directories! 
 *
 *
 */

int  create_the_missing_path(char *pathname){

char buf[SIZE_OF_NAME];
char buf_pathname[SIZE_OF_NAME];
char delimeter = '/';
	
if(!pathname){ //pathname == NULL
INFO("ERROR: pathname is NULL!, can't resolve the path. exiting\n");
exit(1);
}

if(strlen(pathname) == 0){//empty string
INFO("ERROR: pathname is of length 0, can't resolve the path, exiting\n");
exit(1);
}

if(pathname[0] == delimeter){//the path name starts with '/' => this is an absolute path! we need a releative
INFO("ERROR: pathname is given as an absolute-path - can't resolve the path. exiting...\n");
exit(1);
}

memset(buf,0,sizeof(buf));
memset(buf_pathname,0,sizeof(buf_pathname));

strcpy(buf_pathname, pathname);


   char *token;
  
   /* get the first token */
   token = strtok(buf_pathname, "/");

   //TODO remove this debu input:
	if(shouldPrint){
   printf("token == %s\n", token);
	}

   strcat(buf,token);

   if(strcmp(buf,pathname) == 0){
		return 0;
	}
   
   /* walk through other tokens */
   //TODO take out the counter 
   while( token != NULL &&  (1 ||counter > 0)) 
   {
	//TODO release the print!
	if(shouldPrint) {
	printf( " %s\n", token );
	}

	make_dir_if_not_exist(buf);
	
	

	token = strtok(NULL, "/");
	if(token != NULL){
	strcat(buf, "/");
	strcat(buf,token);
	
	 if(strcmp(buf,pathname) == 0){
		return 0;
	}
	}
	//TODO put thi
	if(testMode){
	counter--;
	}
   }



	return 0;
}

//we will delete trailing slashes for directories! 
size_t delete_the_trailing_slash_if_exist(char *pathname, char *resBuf,  int size){



char buf_pathname[SIZE_OF_NAME];
char delimeter = '/';

size_t len;
	
if(!pathname){ //pathname == NULL
INFO("ERROR: pathname is NULL!, can't resolve the path. exiting\n");
exit(1);
}


if(strlen(pathname) == 0){//empty string
INFO("ERROR: pathname is of length 0, can't resolve the path, exiting\n");
exit(1);
}

if(pathname[0] == delimeter){//the path name starts with '/' => this is an absolute path! we need a releative
INFO("ERROR: pathname is given as an absolute-path - can't resolve the path. exiting...\n");
exit(1);
}

//memset(resBuf,0,sizeof(resBuf));
memset(buf_pathname,0,sizeof(buf_pathname));
//char resBuf;

strcpy(buf_pathname, pathname);

while ((len = strlen(buf_pathname)) && (buf_pathname[len - 1] == '/')) {

	
	if(buf_pathname[len - 1] == '/'){
	buf_pathname[len-1] = 0;
	}


}



if(len == 0){//empty string
	INFO("ERROR: pathname is of length 0, can't resolve the path, exiting\n");
	exit(1);
	}

strcpy(resBuf, buf_pathname);
return strlen(resBuf);
}

