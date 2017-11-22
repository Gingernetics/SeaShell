#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//Largest amount of arguments passed as input
const int ARGLIMIT = 20;

//Given a string, returns an output usable by execvp()
char ** parse_args( char * line ){

	//char * string is only used to test the size of strings
	char * string;

	char ** arguments = calloc(ARGLIMIT, sizeof(string));
	char * element = malloc(8);

	int i = 0;

	while((element = strsep(&line, " ")) != NULL){
		arguments[i++] = element;
	}

	arguments[i] = NULL;
	return arguments;
}

int main(int argc, char *argv[]){

	char line[100] = "ls -a -l";
	char **result = parse_args(line);

	int parent = fork();

	if(parent){
		int status;
		wait(&status);
		printf("Parent\n");
	}

	if(!parent){
		//execvp automatically releases memory
		execvp(result[0], result);
	}

	printf("Done\n");
	return 0;
}
