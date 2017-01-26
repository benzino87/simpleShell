/********************************************
 *
 * Author: Jason Bensel
 *         Tyler Miller
 * 	   Lab 2
 *
 * *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


/*******************************************
 *
 * Listens for user input, parses into
 * input into tokens, spawns a child fork
 * and executes a system call with specified
 * tokens. 
 *
 * ****************************************/
int main(int argc, char *argv[]){
	
	//Input from user
	char input[20];
	
	//Parent pid , child pid	
	pid_t pid, child;
	
	//Status of child fork
	int status;

	//Token after splitting user input
	char *token;
	
	//Argument token
	char *myargs[10];

	//Handles user input, spawns child fork
	//executes command
	while(1){
		
		//Request user input
		printf("bennyshell>");
		fgets(input, 20, stdin);
		
		//Get the first token
		token = strtok(input, "\t \n");
		

		int count = 0;
		//Gets remaining tokens 
		while(token != NULL){
			myargs[count] = token;
			token = strtok(NULL, "\t \n");

			count++;
		}

		//Check for quit command, exit the shell
		if(!strcmp(myargs[0], "quit\n")){
			exit(1);
		}

		//Exits on failure to create fork
		else if((pid = fork()) < 0){
			printf("fork failure");
			exit(1);
		}
		
		//Handle standard user input (child)
		//executes syscall
		else if(pid == 0){
			myargs[count] = NULL;
			if(execvp(myargs[0], &myargs[0]) < 0){
				perror("exec failed");
			}
			exit(1);
		}
		
		//Parent awaits death of child then continues
		//iterations of handling user input
		child = waitpid(-1, &status, 0);
		printf("Child PID: %ld process ended\n", (long)child);

	}
	return 0;
}
