#include "seashell.h"

//For readability of code
#define WAITING 1


static void sig_handler(int signo){
	if (signo == SIGINT){
		char message[] = "\n --And thus ends SeaShell. Enjoy your day!-- \n";
		printf("%s", message);
		exit(SIGINT);
	}
}



int main(){

	//Output for Interrupt
	signal(SIGINT, sig_handler);

	char * current_dir;
	char input[1024];

	while(WAITING){
	
		//Input from terminal, halts loop
		current_dir = get_pwd();
		printf("%s-:> ", current_dir);
		fgets(input, sizeof(input), stdin);


		//Splits input by ';'
		char **commands = parse_args(input, ";");

		int i = 0;
		char *line;
		
		//Runs every command provided
		while((line = commands[i++]) != NULL){

			/* Special Conditions */

			//First Space condition
			if (line[0] == ' '){
				printf("' ' is not recognized as a vaild command\n");
				break;
            }

			char **command = parse_args(line, " ");
            
            //Exit condition
			if (strcmp(line, "exit") == 0){
				exit(0);
				break; //Not necessary, but for looks
            }
            
			//Cd condition
			if (strcmp(command[0], "cd") == 0){
			    int ret;
			    if (command[1]){
				    char *directory = command[1];
    				ret = chdir(directory);
    			}
    			else{
    			    ret = chdir(getenv("HOME"));
    			}
    			break;
			}

			//Redirection (< or >) condition

			//Pipe condition

            //Run command
			run_command(command);
		}
	}

	return 0;
}
