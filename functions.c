#include "seashell.h"

//Given a string, returns an array of strings separated by delimiter
char ** parse_args( char * line, char * delimiter ){

	line = remove_char( line, '\n');

	char ** arguments = calloc(20, 8);
	char * element = malloc(8);

	int i = 0;
	while((element = strsep(&line, delimiter)) != NULL){
	    if(strcmp(element, "") != 0){
		    arguments[i++] = element;
		}
	}
	arguments[i] = NULL; 

	return arguments;
}

//Removes unwanted characters from a string array
char * remove_char( char * line, char bad_char){
	char *src, *dest;

	src = dest = line;
	while(*src != '\0'){
    		if (*src != bad_char){
        		*dest = *src;
       			dest++;
    		}
    		src++;
	}
	*dest = '\0';
	return line;
}

//Finds the pwd of the shell
char * get_pwd(){
    long size;
    char *buf;
    char *pwd;

    size = pathconf(".", _PC_PATH_MAX);

    if ((buf = (char *)malloc((size_t)size)) != NULL)
        pwd = getcwd(buf, (size_t)size);
        
    return pwd;
}


void run_command(char ** command){
   
			int parent = fork();

			if(parent){
				int status;
				wait(&status);
			}

			if(!parent){
				//execvp automatically releases memory
				execvp(command[0], command);	
			}
}
