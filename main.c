#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#include "seashell_functions.h"

//For readability of code
#define WAITING 1

//Largest amount of arguments passed as input
const int ARGLIMIT = 20;


static void sig_handler(int signo){
	if (signo == SIGINT){
		char message[] = "\n --And thus ends SeaShell. Enjoy your day!-- \n";
		printf("%s", message);
		exit(SIGINT);
	}
}



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


char ** split_line(char * line, char * delimiter){
	int i, j = 0;
	char *token[1024];
   	token[i] = strtok(line, delimiter);

    	while (token[i] != NULL) {
        	i++;
        	token[i] = strtok(NULL, delimiter);
    	}

    	for (j=0; j<=i-1; j++) {
        	printf("%s\n", token[j]);
    	}
	return token;
}

int main(){

	//Output for Interrupt
	signal(SIGINT, sig_handler);


	char line[1024];

	while(WAITING){

		//Input from terminal, halts loop
		fgets(line, sizeof(line), stdin);
		record_in_log(line);


		//Splits input by ';'
		int i;
		char *token[1024];
		printf("%s\n", line);
		token = split_line(line, ";");

		// Special Conditions /

		//Exit condition
		if (strcmp(line, "exit\n") == 0)
			exit(0);

		//Cd condition
		//Possibility that a command ending in cd triggers
		//if (strstr(line, "cd ") == 0)

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
