/*
 * Implements the following precedence graph
 *    |<-----
 *    A     |
 *  /   \   |
 * B     C  |
 *  \   /   |
 *    D     |
 *    ------|
 * with threads and POSIX semaphores
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h> // For O_CREAT and O_EXCL

// Global semaphores
sem_t *semB, *semC, *semD;

// Flag to control the loop
int cycles = 3;

// Thread function for A
void *utilityA(void* arg) {
    while (cycles > 0) {
        sem_wait(semD); // Wait for D to signal
        printf("A\n");
        sem_post(semB); // Signal B to start
        sem_post(semC); // Signal C to start
    }
    return NULL;
}

// Thread function for B
void *utilityB(void* arg) {
    while (cycles > 0) {
        sem_wait(semB); // Wait for A to signal
        printf("B\n");
        sem_post(semD); // Signal D that B is complete
    }
    return NULL;
}

// Thread function for C
void *utilityC(void* arg) {
    while (cycles > 0) {
        sem_wait(semC); // Wait for A to signal
        printf("C\n");
        sem_post(semD); // Signal D that C is complete
    }
    return NULL;
}

// Thread function for D
void* utilityD(void* arg) {
    while (cycles > 0) {
        sem_wait(semD); // Wait for B to complete
        sem_wait(semD); // Wait for C to complete
        printf("D\n");
        cycles--; // Decrement the cycle counter

        sem_post(semD); // Signal A to start again
    }
    return NULL;
}

int main() {

    pthread_t th_A, th_B, th_C, th_D;

    // Ensure previous semaphores are unlinked
    sem_unlink("/semB");
    sem_unlink("/semC");
    sem_unlink("/semD");

    // Create semaphores
    semB = sem_open("/semB", O_CREAT | O_EXCL, 0644, 0);
    semC = sem_open("/semC", O_CREAT | O_EXCL, 0644, 0);
    semD = sem_open("/semD", O_CREAT | O_EXCL, 0644, 1);

    if (semB == SEM_FAILED || semC == SEM_FAILED || semD == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    // Create threads
    pthread_create(&th_A, NULL, utilityA, NULL);
    pthread_create(&th_B, NULL, utilityB, NULL);
    pthread_create(&th_C, NULL, utilityC, NULL);
    pthread_create(&th_D, NULL, utilityD, NULL);

    // Wait for threads to finish
    pthread_join(th_A, NULL);
    pthread_join(th_B, NULL);
    pthread_join(th_C, NULL);
    pthread_join(th_D, NULL);

    // Cleanup semaphores
    sem_close(semB);
    sem_close(semC);
    sem_close(semD);
    sem_unlink("/semB");
    sem_unlink("/semC");
    sem_unlink("/semD");

    return 0;
}
