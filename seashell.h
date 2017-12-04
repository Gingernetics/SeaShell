#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

char ** parse_args( char * , char * );
char * get_pwd();
void run_command(char ** );
char * remove_char( char * , char );
