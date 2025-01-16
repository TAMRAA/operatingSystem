#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Dictionary

/*
    The system() function executes the command stored in str as if it were typed in the shell.
    In this case, it calls the program recursively with a decremented argument
    Usually, system() starts a new instance of the program with the updated argument
*/

int main(int argc, char **argv){

    int n;
    char str[10];

    n = atoi(argv[1]);

    if(n > 0){
        fprintf(stdout,"%d\n",n);
        sprintf(str,"%s %d",argv[0], n-1);
        system(str);
    }

    fprintf(stdout,"End!\n");
    
    return EXIT_SUCCESS;
}