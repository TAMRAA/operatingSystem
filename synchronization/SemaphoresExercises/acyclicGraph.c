/*
 * Implements the following precedence graph
 *    A
 *  /   \
 * B    C
 *  \  /
 *   D
 * with threads and POSIX semaphores
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

// Global semaphores
sem_t *semA, *semBC;

// Thread functions
void* threadB(void* arg) {
    sem_wait(semA); // Wait for A to complete
    printf("B\n");
    sem_post(semBC); // Signal that B is complete
    pthread_exit(NULL);
}

void* threadC(void* arg) {
    sem_wait(semA); // Wait for A to complete
    printf("C\n");
    sem_post(semBC); // Signal that C is complete
    pthread_exit(NULL);
}

void* threadD(void* arg) {
    sem_wait(semBC); // Wait for B to complete
    sem_wait(semBC); // Wait for C to complete
    printf("D\n");
    pthread_exit(NULL);
}

int main(void) {
    pthread_t threadB, threadC, threadD;

    // Create semaphores
    semA = sem_open("/semA", O_CREAT | O_EXCL, 0644, 0);
    semBC = sem_open("/semBC", O_CREAT | O_EXCL, 0644, 0);

    // Check for errors
    if (semA == SEM_FAILED || semBC == SEM_FAILED) {
        perror("sem_open failed");
        exit(1);
    }

    // Create threads
    pthread_create(&threadB, NULL, threadB, NULL);
    pthread_create(&threadC, NULL, threadC, NULL);
    pthread_create(&threadD, NULL, threadD, NULL);

    // Perform task A
    printf("A\n");
    sem_post(semA); // Signal B to start
    sem_post(semA); // Signal C to start

    // Wait for threads to finish
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);
    pthread_join(threadD, NULL);

    // Cleanup semaphores
    sem_close(semA);
    sem_close(semBC);
    sem_unlink("/semA");
    sem_unlink("/semBC");

    return 0;
}