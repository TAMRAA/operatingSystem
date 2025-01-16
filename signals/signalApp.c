#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


/* 
  This code example effectively demonstrates how processes can communicate using signals
  and how signal handling works within a C program
*/


// Signal handler function
static void handleSignal(int signo) {
    /* 
        This function handles incoming signals.
        It checks which signal was received and prints a message accordingly
    */

    if (signo == SIGUSR1) {
        fprintf(stdout, "Received SIGUSR1\n");
    } else if (signo == SIGUSR2) {
        fprintf(stdout, "Received SIGUSR2\n");
    } else {
        fprintf(stdout, "Received signal %d\n", signo);
    }
    return;
}

// Function executed by the parent process
void parentProcess(pid_t child_pid) {
    printf("Parent: Start (S11)\n");
    sleep(1); // This pause is used to ensure the child process is set up before sending a signal.

    // The `kill` function sends a signal (SIGUSR1) to the specified process (child process).
    kill(child_pid, SIGUSR1);
    printf("Parent: Sent SIGUSR1 to child (S12)\n");

    // The `pause()` function causes the parent process to wait until it receives a signal.
    pause();
    printf("Parent: Received response (S13)\n");
    return;
}

// Function executed by the child process
void childProcess() {
    if (fork() > 0) {
        // This is the first child process.
        printf("Child: Start (S21)\n");

        // The `pause()` function makes this process wait until it receives a signal.
        pause();
        printf("Child: Received signal and responding (S23)\n");

        // The `kill` function sends a signal (SIGUSR2) to the parent process.
        kill(getppid(), SIGUSR2);

        // `wait(NULL)` waits for the second child to terminate.
        wait(NULL);
    } else {
        // This is the second child process.
        printf("Second child: Start (S22)\n");

        // The second child exits immediately after starting.
        exit(0);
    }
    printf("Child: End (S24)\n");
    return;
}

int main(void) {
    
    pid_t pid;

    // Set up signal handlers for the main process. `signal()` assigns `handle_signal`
    // to handle `SIGUSR1` and `SIGUSR2`. If it fails to set the handler, an error message is printed.
    if (signal(SIGUSR1, handleSignal) == SIG_ERR) {
        fprintf(stderr, "Error: Cannot handle SIGUSR1\n");
        return 1;
    }
    if (signal(SIGUSR2, handleSignal) == SIG_ERR) {
        fprintf(stderr, "Error: Cannot handle SIGUSR2\n");
        return 1;
    }

    printf("Main process: Starting (S20)\n");

    // The `fork()` system call creates a new process.
    pid = fork();

    if (pid > 0) {
        // This is the parent process.
        parentProcess(pid);

        // `wait(NULL)` waits for the child process to finish before the parent continues.
        wait(NULL);
    } else if (pid == 0) {
        // This is the child process.
        childProcess();
        exit(0); // Ensure the child exits after completing its tasks.
    } else {
        // If `fork()` returns a negative value, it indicates an error in creating the process.
        fprintf(stderr, "Error: Fork failed\n");
        return 1;
    }

    printf("Main process: Ending (S25)\n");
    return 0;
}
