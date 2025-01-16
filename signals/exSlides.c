/*
 *  Precedence graph with signal, kill & pause
 *  and race conditions !!!
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// function prototypes
void signalHandler(int signo);
void functionParent(pid_t cpid);
void functionChild();

// Main function
int main(void){
    
    pid_t pid;

    pid = fork();

    if(pid < 0){
        fprintf(stderr,"Fork Failed :(\n");
        exit(EXIT_FAILURE);
    }else if(pid > (pid_t ) 0){
        functionParent(pid);
        wait(NULL);
    }else{
        functionChild();
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}


// function declarations

void signalHandler(int signo){
    if(signo == SIGUSR1){
        fprintf(stdout,"SIGUSR1 Received :)\n");
    }else if(signo == SIGUSR2){
        fprintf(stdout,"SIGUSR2 Received :)\n");
    }else{
        fprintf(stdout,"Signal %d Received :)\n", signo);
    }
}


void functionParent(pid_t cpid){
    
    fprintf(stdout,"Function parent #1 activated successfully :)\n");
    fprintf(stdout,"Sleeping for 1 second...zzz\n");
    sleep(1);

    fprintf(stdout,"Killing the signal XO\n");
    kill(cpid,SIGUSR1);
    fprintf(stdout,"Signal killed.\n");

    fprintf(stdout,"Pausing the signal...\n");
    pause();

    fprintf(stdout,"Signal paused ||\n");



    fprintf(stdout,"Function parent is finished successfully :)\n");
    return;
}

void functionChild(){
    pid_t pid;

    pid = fork();

    if(pid < 0){
        fprintf(stderr,"Fork Failure :(\n");
        exit(EXIT_FAILURE);
    }else if(pid > 0){

        fprintf(stdout,"Function child #2 activated successfully :)\n");
        fprintf(stdout,"Sleeping for 1 second...zzz\n");
        sleep(1);

        fprintf(stdout,"Killing the second signal XO\n");
        kill(pid,SIGUSR2);
        fprintf(stdout,"Second Signal killed.\n");

        fprintf(stdout,"Pausing the second signal...\n");
        pause();
        fprintf(stdout,"Second Signal paused ||\n");

        wait(NULL);

    }else{
        fprintf(stdout,"I am the grandChild :)\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout,"function Child is finished :)\n");

}