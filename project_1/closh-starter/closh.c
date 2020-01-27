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

#define true 1
#define false 0

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
        
		int pid = getpid();
		printf("closh pid: %d", pid);
		
		while(count--)
		{
			pid = fork();
			
			if(!pid)
			{
				printf("%s pid: %d",cmdTokens[0], getpid());
				execvp(cmdTokens[0], cmdTokens);
			}
			else if(!parallel)
			{
				sleep(timeout);
				kill(pid, SIGKILL);
			}
			
			if(count==0)exit(1);
		}
		
		
        // doesn't return unless the calling failed
        printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
        exit(1);        
    }
}

