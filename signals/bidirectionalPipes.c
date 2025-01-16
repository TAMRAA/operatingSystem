

/* Overview of the Code
-----------------------

The code creates a unidirectional pipe that both the parent and child processes use to communicate.
The behavior of the communication depends on the command-line argument 
(argv[1]) passed when running the program
The program runs an infinite loop in both the parent and child processes,
continuously writing to and reading from the pipe, based on the argument provided 

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


int main(int argc, char **argv){
    
    int fd[2];
    char c;

    // bidirectional => Phone communication => "PC"
    
    setbuf (stdout, 0);
    pipe (fd);

    if (fork()!=0) {
        while (1) {
            if (strcmp(argv[1],"P")==0||strcmp(argv[1],"PC")==0) {
                c = 'P';
                fprintf (stdout, "Parent writes %c\n", c);
                write (fd[1], &c, 1);
            }
            sleep (2);
            if (strcmp(argv[1],"C")==0|| strcmp(argv[1],"PC")==0) {
                read (fd[0], &c, 1);
                fprintf (stdout, "Parent reads %c\n", c);
            }   
            sleep (2);
        }
        wait (NULL);
    } 
    else {
        while (1) {
            if (strcmp(argv[1],"P")==0||strcmp(argv[1],"PC")==0) {
                read (fd[0], &c, 1);
                fprintf (stdout, "Child reads %c\n", c);
            }
            sleep (2);
            if (strcmp(argv[1],"C")==0||strcmp(argv[1],"PC")==0) {
                c = 'C';
                fprintf (stdout, "Child writes %c\n", c);
                write (fd[1], &c, 1);
            }

            sleep (2);
        }
        
        exit (0);
    }
    
    return EXIT_SUCCESS;
}