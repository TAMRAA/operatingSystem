#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define SIZE  524288
int fd[2];

static void signalHandler(int signo) {
    if (signo == SIGUSR1) {
        printf("\nReceived SIGUSR1 -> stop\n");
        exit(0);
    } else if (signo == SIGUSR2) {
        printf("\nReceived SIGUSR2 -> stop\n");
    }
}

int main(int argc, char **argv) {
    int i, n, nR, nW;
    char c = '1';
    setbuf(stdout, NULL);

    // Install Signal Handler
    if (signal(SIGUSR1, signalHandler) == SIG_ERR) {
        fprintf(stderr, "Signal Handler Error.\n");
        return EXIT_FAILURE;
    }
    if (signal(SIGUSR2, signalHandler) == SIG_ERR) {
        fprintf(stderr, "Signal Handler Error.\n");
        return EXIT_FAILURE;
    }

    // Create pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    n = 0;
    if (fork()) {
        // Parent process
        fprintf(stdout, "\nParent PID=%d\n", getpid());
        sleep(1);
        for (i = 0; i < SIZE; i++) {
            nW = write(fd[1], &c, 1);
            if (nW == -1) {
                perror("write");
                break;
            }
            n += nW;
            fprintf(stdout, "W: %d\r", n);
        }
        close(fd[1]); // Close the write end
        wait(NULL);
    } else {
        // Child process
        fprintf(stdout, "Child PID=%d\n", getpid());
        sleep(10);
        
        for (i = 0; i < SIZE; i++) {
            nR = read(fd[0], &c, 1);
            if (nR == -1) {
                perror("read");
                break;
            }
            n += nR;
            fprintf(stdout, "R: %d\r", n);
        }
        fprintf(stdout,"R: %d\n",n);
        close(fd[0]); // Close the read end
    }

    return EXIT_SUCCESS;
}