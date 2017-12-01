#include "seashell.h"

//Largest amount of arguments passed as input
const int ARGLIMIT = 20;

//Given a string, returns an output usable by execvp()
char ** parse_args( char * line, char * delimiter ){

	line = remove_char( line, '\n');

	char ** arguments = calloc(ARGLIMIT, 8);
	char * element = malloc(8);

	int i = 0;
	while((element = strsep(&line, delimiter)) != NULL){
		arguments[i++] = element;
	}
	arguments[i] = NULL; 

	return arguments;
}


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

void record_in_log(char * line){
	int fd = open("history.log", O_APPEND | O_WRONLY, 0644);
	write(fd, line, (sizeof(line) - 1));
	close(fd);
}
