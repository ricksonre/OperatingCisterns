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
#include <wait.h>
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
       
        //declare an array of max length 9
        //initialises all of the values to -1
        int childs[9];
        for(int i=0;i<9;i++)
            childs[i]=-1;
        int index = 0;
        //initialise index to 0
        //prints the current process id
        int pid = getpid();
        printf("closh pid: %d\n", pid);
 
 
        while(count--)
        {
            //forks and gets the child id
            int pid = fork();
           
            //if fork failed to create a new process
            //  prints the error and exits current run
            if(pid <0)
            {
                printf("Failed to create child process!\n");
            }
            //if the process is a child process
            //  create a new instance of the selected program
            else if(!pid)
            {
                printf("%s pid: %d\n",cmdTokens[0], getpid());
                //print pid of program and what command it is going to execute
                //tries to susbtitute child for desired process
                //  in case of error prints and exits run
                if(execvp(cmdTokens[0], cmdTokens)==-1)
                {
                    // doesn't return unless the calling failed
                    printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
                }
            }
            else//parent adds 1 to index and writes it's child's pid to that index of the array
            {
                childs[index++] = pid;
            }
            //if the code is suposed to run sequentially
            if(!parallel)
            {
				//if the timeout is not 0
				// 	sleeps for the set amount of time and kill the child process afterwards
                if(timeout)
                {
                    sleep(timeout);
                    kill(pid, SIGKILL);
                }
				//if the timeout is zero
				//	waits for the proccess to end to progress
                else
                {
                    int status = -1;
                    wait(&status);
                }
            }
        }
   
	    //If it is supossed to run parallel
        if(parallel)
        {
            //if there is a set timeout 
            //	sleeps for set time and kill all child processes afterwards
            if(timeout)
            {
                sleep(timeout);
                for(int i=0;i<9;i++)//loop through all elements of the array
                {
                    if(childs[i] != -1)//if the element holds a child ID try to kill it
                    {
                        kill(childs[i], SIGKILL);
                    }
                }
            }
            //if there is a no timeout 
            //	waits until no child process is running
            else
            {
                for(int i=0;i<9;i++)//loops through all elements of array
                {
                    int status = -1;
                    wait(&status);//waits for all elements to be done running
                }
            }
        }
    }
    return 0;//execution complete, return
}