SeaShell
by Jan Kowalski

Features:
	Forks and executes commands
	Spaces do not impact command beyond the first character of a command
	Displays the current working directory in prompt
	Parses multiple commands on one line
	Goodbye on interrupt


Attempted:
    Could not get redirection to work
	Could not get pipes to work

Bugs:
	No allocated memory is freed

	
Files & Function Headers:

functions.c
	Handles all line parsing fucntions


	/*======== char ** parse_args ==========
	Inputs:  char * line, 
        	  char * delimiter
	Returns: An array of tokens previously separated by delimiter

    -If line contains multiple tokens separated by delimiter, this 
	function will put each token into an array of strings
	-If delimiter does not appear, the whole string is returned
	====================*/

	/*======== char * get_pwd() ==========
	Inputs: 
	Returns: A string representation of the current working directory

    Finds the pwd of the shell
	====================*/
	
	/*======== void run_command(char ** command) ==========
	Inputs: An array of tokens representing the command
	Returns: 

    -This function exists to show knowledge of execvp and runs the command
	====================*/

	/*======== char * remove_char( char * line, char bad_char) ==========
	Inputs:  char *line 
	Returns: Pointer to the beginning of line

    -Removes unwanted characters from a string array
    -If bad_char does not appear in the string, the string in returned
	====================*/

main.c
	Handles the edge conditions for function calls and calls appropriate functions

    First Space condition 
        If the first char of an argument is a space, an error will be sent to prompt
        
    Exit condition
        If exit is called as an argument, the process ends

    Cd condition
        If cd is called with a valid argument, the current working directory is changed to argument
        Else, the current working directory is changed to home
