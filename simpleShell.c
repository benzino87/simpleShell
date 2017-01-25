/********************************************
 *
 * Author: Jason Bensel
 * 	   Lab 2
 *
 * *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){
	//Input from user
	char input[20];

	pid_t pid, child;
	int status;

	//Token after splitting user input
	char *token;
	
	//Argument token
	char *myargs[10];

	//Listen to for user command
	while(1){
		printf("bennyshell>");
		fgets(input, 20, stdin);
		
		//Get the first token
		token = strtok(input, "\t \n");
		
		int count = 0;
		//Get remaining tokens
		while(token != NULL){
			printf("%s\n", token);
			myargs[count] = token;
			token = strtok(NULL, "\t \n");

			count++;
		}

		//Check for quit command, exit the shell
		if(!strcmp(myargs[0], "quit\n")){
			exit(1);
		}
		else if((pid = fork()) < 0){
			printf("fork failure");
			exit(1);
		}
		else if(pid == 0){
			printf("Hello from child %ld\n", (long) getpid());
			myargs[count] = NULL;
			if(execvp(myargs[0], &myargs[0]) < 0){
				perror("exec failed");
			}
			exit(1);
		}
		else {
			child = waitpid(-1, &status, 0);
		}

	}
	return 0;
}
