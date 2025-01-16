#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define numProccesses 5

/*
    This program is a simple simulation of process scheduling in a system using semaphores, pipes, and signals
    to manage synchronization between processes :)
*/

// Data Structures

// Semaphores
typedef int *semaphore;
semaphore clock, semArray[numProccesses];


// Global Variables
int deadline[numProccesses];
int interval[numProccesses];
int pipeStorage[20];
int pipeIndex = 0;
int time = 0;

// Utility Functions

// Function to create a semaphore
semaphore makeSemaphores() {

    int *sem;
    sem = &pipeStorage[pipeIndex];
    pipeIndex += 2; // Increment by 2 for read/write ends
    pipe(sem); // Create a pipe for the semaphore
    return sem; // Return the semaphore

}

// WAIT function for semaphore
void WAIT(semaphore s) {
    int junk;
    if (read(s[0], &junk, 1) <= 0) {
        fprintf(stderr, "ERROR WAIT :(\n");
        exit(1);
    }
}

// SIGNAL function for semaphore
void SIGNAL(semaphore s) {
    if (write(s[1], "s", 1) <= 0) {
        fprintf(stderr, "ERROR SIGNAL :(\n");
        exit(1);
    }
}


// Example process function for process 0
void process0() {

    int pid;
    while (1) {
        WAIT(semArray[0]); // Wait for semaphore signaling
        pid = getpid(); // Get the process ID
        printf("I'm process %d\n", pid);
        system("date"); // Print the current date and time
    }
}

// Example process function for process 1
void process1() {

    int pid;
    while (1) {
        WAIT(semArray[1]); // Wait for semaphore signaling
        pid = getpid(); // Get the process ID
        printf("I'm process %d\n", pid);
        system("date"); // Print the current date and time
    }
}

// Signal handler for alarm
void catcher() {
    printf("tick\n");
    SIGNAL(clock);              // Signal the clock semaphore
    signal(SIGALRM, catcher);   // Reset signal handler
}

// Function to manage the alarm
void theAlarm() {
    signal(SIGALRM, catcher); // Set the signal handler
    while (1) {
        alarm(1); // Set an alarm for 1 second
        pause(); // Wait for the alarm signal
    }
}

// Main function
int main() {

    int i;
    // Initialize semaphores
    clock = makeSemaphores();

    for (i = 0; i < numProccesses; i++) {
        // Create semaphores for each process
        semArray[i] = makeSemaphores();
    }

    // Initialize the scheduler
    interval[0] = 5;
    interval[1] = 7;

    deadline[0] = 5;
    deadline[1] = 7;

    // Create child processes
    if ((i = fork()) == 0){
        process0();
    }

    if (fork() == 0){
        process1();
    }

    if (fork() == 0){
        theAlarm();
    }

    // Control the scheduling
    while (1) {

        WAIT(clock); // Wait for the clock signal
        time++; // Increment the time

        for (i = 0; i < numProccesses; i++) {
            if (deadline[i] <= time) { // Check if deadlines are met
                deadline[i] = time + interval[i]; // Reset deadline
                printf("WAKE UP process %d at time %d\n", i, time);
                SIGNAL(semArray[i]); // Signal the corresponding process
            }
        }
    }

    return EXIT_SUCCESS;
}