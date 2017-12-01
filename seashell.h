#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>


char ** parse_args( char * , char * );
char * remove_char( char * , char );
void record_in_log(char * );
