/*
    This C program demonstrates inter-process communication (IPC) using a pipe
    The program creates a parent and child process where:
    1) The parent process writes a series of characters to a pipe
    2) The child process reads those characters from the pipe after a delay
*/


#include <stdio.h>   
#include <stdlib.h>  
#include <unistd.h>   
#include <sys/types.h> 

// 512 KB * 1024 bytes
#define SIZE (274 * 1024)

// Array for the file descriptors used by the pipe
// => fd[0] for reading, fd[1] for writing
int fd[2]; 

int main() {

    int n = 0;
    int i;
    int nR;
    int nW; 
    char c = '1';


    // Disable output buffering for stdout to see immediate results
    /* setbuf(stdout, NULL); */

    // Create a pipe and check for success
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    if (fork()){ 
        // Parent process block
        fprintf(stdout, "\nParent PID=%d\n", getpid());
        sleep(10); // Delay to allow the child to set up and read later

        // Write `SIZE` bytes to the pipe, one at a time
        for (i = 0; i < SIZE; i++) {
            // Write 1 byte to the write end of the pipe
            nW = write(fd[1], &c, 1);
            if (nW == -1) {
                perror("Write error");
                exit(EXIT_FAILURE);
            }

            n += nW;

        }
        // Display number of bytes written
        fprintf(stdout, "\ni wrote %d bytes :)\n", n); 
    } else {
        // Child process block
        fprintf(stdout, "Child PID=%d\n", getpid());

        // Delay to simulate a time gap before reading starts
        sleep(10);

        // Read `SIZE` bytes from the pipe, one at a time
        for (i = 0; i < SIZE; i++) {
            // Read 1 byte from the read end of the pipe
            nR = read(fd[0], &c, 1);
            if (nR == -1) {
                perror("Read error");
                exit(EXIT_FAILURE);
            }
            n += nR;
        }
        // Display number of bytes rea
        fprintf(stdout, "\ni read %d bytes :)\n", n);
    }


    return EXIT_SUCCESS;
}