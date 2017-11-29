#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "seashell_functions.h"

//For readability of code
#define WAITING 1

//Largest amount of arguments passed as input
const int ARGLIMIT = 20;


//Given a string, returns an output usable by execvp()
char ** parse_args( char * line ){

	line = remove_char( line, '\n');

	char ** arguments = calloc(ARGLIMIT, 8);
	char * element = malloc(8);

	int i = 0;

	while((element = strsep(&line, " ")) != NULL){
		arguments[i++] = element;
	}

	arguments[i] = NULL;
	return arguments;
}


char * remove_char( char * input, char bad_char){
	char *src, *dest;

	src = dest = input;
	while(*src != '\0'){
    		if (*src != bad_char){
        		*dest = *src;
       			dest++;
    		}
    		src++;
	}
	*dest = '\0';
	return input;
}


int main(){

	char line[1024];

	while(WAITING){

		//Exit condition
		if (strcmp(line, "exit\n") == 0)
			exit(0);

		//Input from terminal, halts loop
		fgets(line, sizeof(line), stdin);

		//Strsep by ;, then while loop
		char **result = parse_args(line);

		int parent = fork();

		if(parent){
			int status;
			wait(&status);
		}

		if(!parent){
			//execvp automatically releases memory
			execvp(result[0], result);
		}
	}
	return 0;
}
