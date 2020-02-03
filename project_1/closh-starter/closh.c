/* 
	closh.c - COSC 315, Winter 2020
	
	Names:
	Rickson Reichmann
	Ren Lin
	Carther Phillips
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <omp.h>

#define true 1
#define false 0

int seqClosh(int count, int timeout, char** cmdTokens);
int parraClosh(int count, char** cmdTokens);
// tokenize the command string into arguments - do not modify
void readCmdTokens(char* cmd, char** cmdTokens) 
{
    cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
    int i = 0;
    cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
    while (cmdTokens[i++] && i < sizeof(cmdTokens)) 
	{
        cmdTokens[i] = strtok(NULL, " ");
    }
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
    char c = getchar();
    while (getchar() != '\n');
    return c;
}

// main method - program entry point
int main() 
{
    char cmd[81]; // array of chars (a string)
    char* cmdTokens[20]; // array of strings
    int count; // number of times to execute command
    int parallel; // whether to run in parallel or sequentially
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)
    
    while (true) 
	{ // main shell input loop
	
        // begin parsing code - do not modify
        printf("closh> ");
        fgets(cmd, sizeof(cmd), stdin);
        if (cmd[0] == '\n') 
			continue;
        readCmdTokens(cmd, cmdTokens);
		
        do 
		{
            printf("  count> ");
            count = readChar() - '0';
        } while (count <= 0 || count > 9);
        
        printf("  [p]arallel or [s]equential> ");
        parallel = (readChar() == 'p') ? true : false;
		
        do 
		{
            printf("  timeout> ");
            timeout = readChar() - '0';
        } while (timeout < 0 || timeout > 9);
        // end parsing code
        
        
        ////////////////////////////////////////////////////////
        //                                                    //
        // TODO: use cmdTokens, count, parallel, and timeout  //
        // to implement the rest of closh                     //
        //                                                    //
        // /////////////////////////////////////////////////////
        

		//prints the current process id
		int pid = getpid();
		printf("closh pid: %d\n", pid);

		if(parallel)//if parallel run the parraClosh() method
		{
			parraClosh(count, cmdTokens);
		}
		else//if not parallel run the seqClosh() method
		{
			seqClosh(count, timeout, cmdTokens);
		}
    }
	
	return 0;
}

int parraClosh(int count, char** cmdTokens)
{
	int retNum = 0;//setup a return number

	#pragma omp parallel num_threads(count)//initialise multithreaded section with count threads
    {
		int pid = fork();//each thread forks
		if(pid <0)
		{
			printf("Failed to create child process!\n");//error handling for failed fork
			retNum = -1;
		}
		else if(!pid)//if I am the child
		{
			printf("%s pid: %d\n",cmdTokens[0], getpid());//print my pid as well as what command I am going to run
			
			//tries to susbtitute child for desired process
			//	in case of error prints and exits run
			if(execvp(cmdTokens[0], cmdTokens)==-1)
			{
				// doesn't return unless the calling failed	
				printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
				retNum = -1;
				if(omp_get_thread_num())
					exit(0);
			}
		}
	}
	
	return retNum;//returns at end of method
}
int seqClosh(int count, int timeout, char** cmdTokens)
{
	int retNum = 0;//setup of return number

	while(count--)
		{
			//forks and gets the child id
			int pid = fork();
			
			//if fork failed to create a new process 
			//	prints the error and exits current run
			if(pid <0)
			{
				printf("Failed to create child process!\n");
				retNum = -1;
			}
			//if the process is a child process
			//	create a new instance of the selected program
			else if(!pid)
			{
				printf("%s pid: %d\n",cmdTokens[0], getpid());
				
				//tries to susbtitute child for desired process
				//	in case of error prints and exits run
				if(execvp(cmdTokens[0], cmdTokens)==-1)
				{
					// doesn't return unless the calling failed	
					printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
					retNum = -1;
				}
			}
			//if the code is suposed to run sequentially and timeout != 0
			// sleeps for the set amount of time and kill the child process afterwards
			else if(timeout)
			{
				sleep(timeout);
				kill(pid, SIGKILL);
			}
		}
	return retNum;
}

