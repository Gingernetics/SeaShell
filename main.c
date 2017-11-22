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

	char ** arguments = calloc(20, 8);
	char * element = malloc(8);

	int i = 0;
	/*
	printf("%s\n", strsep(&line, " "));
	printf("%s\n", strsep(&line, " "));
*/
/*
	while((element = strsep(&line, " ")) != NULL){
		arguments[i++] = element;
		printf("%s\n", element);
	}
*/
	//arguments[i] = NULL;
	return arguments;
}

int main(){

	char line[100];
	scanf("%s", line);
	printf("%s\n", line);
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

	return 0;
}
