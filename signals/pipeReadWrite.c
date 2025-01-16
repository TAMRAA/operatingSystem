/*
    This C program demonstrates inter-process communication (IPC) using a pipe.
    It creates a parent and a child process where:
    1) The parent process writes a character to the pipe.
    2) The child process reads that character from the pipe and displays it.


    DICTIONARY
    ----------
    1) pipe(file) sets up a unidirectional data channel
    2) file[0]: The read end of the pipe
    3) file[1]: The write end of the pipe

    REMARK
    ------
    1) The parent write to child
    2) Child read from parent

    Blocking
    --------
    Blocking Behavior: If the reading process tries to read from an empty pipe
    or the writing process tries to write when the read end is closed,
    the processes may block or encounter errors
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main() {

    int n;
    int file[2];
    char cW = 'x';
    char cR ='\0';
    
    pid_t pid;


    if(pipe(file) == 0){
        
        fprintf(stdout,"Pipe created Successfully :)\n");
        
        pid = fork();

        if(pid < 0){
            fprintf(stderr,"Fork Failed :(\n");
            exit(EXIT_FAILURE);

        }else if(pid == 0){
            fprintf(stdout,"Reading from parent process...\n");
            close(file[1]);
            n = read(file[0], &cR, 1);
            fprintf(stdout,"Read %d bytes => Character = %c\n", n, cR);
            exit(EXIT_SUCCESS);
        }else{
            fprintf(stdout,"Writing to child process...\n");
            close(file[0]);
            n = write(file[1], &cW, 1);
            fprintf(stdout,"Wrote %d bytes => Character = %c\n", n, cW);
        }
    }

    return EXIT_SUCCESS;

}
