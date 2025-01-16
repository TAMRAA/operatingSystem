#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function Prototype
void P356();


// Main Function
int main () {
    
    pid_t pid;
    printf ("S1\n");
    if ( (pid = fork())==-1 ){
        fprintf(stderr,"can't fork" );
    }
    
    if ( pid == 0 ){
        P356();
    }else{
        printf ("S2\n");
        printf ("S4\n");
        while (wait((int *)0)!= pid);
        printf ("S7\n");
        exit (0);
    }
    return EXIT_SUCCESS;
}

void P356() {
    pid_t pid;
    printf ("S3\n");
    if ( ( pid = fork() ) == -1 ){
        fprintf(stderr,"can't fork" );
    }
    
    if (pid > 0 ){
        printf ("S5\n");
        while (wait((int *)0)!=pid );
    } else {
        printf ("S6\n");
        exit (EXIT_SUCCESS);
    }
    exit (EXIT_SUCCESS);
}