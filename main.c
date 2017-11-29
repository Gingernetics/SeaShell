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



int main(){

	//Output for Interrupt
	signal(SIGINT, sig_handler);


	char input[1024];

	while(WAITING){

		//Input from terminal, halts loop
		fgets(input, sizeof(input), stdin);
		record_in_log(input);


		//Splits input by ';'
		char **commands = parse_args(input, ";");


		int i = 0;
		char *line;
		//Runs every command provided
		while((line = commands[i++]) != NULL){

			/* Special Conditions */

			//Exit condition
			if (strcmp(line, "exit\n") == 0)
				exit(0);

			char **command = parse_args(line, " ");


			//Cd condition
			//Possibility that a command ending in cd triggers
			//if (strstr(line, "cd ") == 0)

			//Strsep by ;, then while loop

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
	}

	return 0;
}
