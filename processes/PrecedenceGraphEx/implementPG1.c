#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){

    pid_t pid;

    fprintf(stdout,"S1\n");

    pid = fork();

    if(!pid){
        sleep(2);
        fprintf(stdout,"S3\n");
        exit(0);
    }else{
        sleep(2);
        fprintf(stdout,"S2\n");

        /*
            It’s a way of saying "I don’t care about the exit status;
            just let me know when a child process has finished
        */
        wait((int *) 0);
    }

    fprintf(stdout,"S4\n");
    pid = fork();
    if(!pid){
        sleep(2);
        fprintf(stdout,"S6\n");
        exit(1);
    }else{
        sleep(2);
        fprintf(stdout,"S5\n");
        wait((int *) 0);
    }

    fprintf(stdout,"S7 :)\n");

    return EXIT_SUCCESS;
}