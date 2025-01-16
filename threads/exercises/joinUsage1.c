#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define numThreads 3



// Task for each thread
void* threadTask(void* arg) {

    int taskNumber = (intptr_t) arg;
    double result = 0.0;

    sleep(1);

    // a simple loop summing random numbers
    for (int i = 0; i < taskNumber; i++) {
        result += (double) random();
    }

    // Print results
    printf("Thread %d: Computed result = %e\n", taskNumber, result);

    // Return the taskNumber as exit status
    pthread_exit( (void*) (long) taskNumber);
}

int main(void) {

    pthread_t threads[numThreads];
    int taskNumbers[numThreads];
    void *returnValue;

    // Creating threads
    for (int i = 0; i < numThreads; i++){

        taskNumbers[i] = i + 1;  // Assign a unique task number to each thread

        printf("Creating thread %d\n", taskNumbers[i]);

        // Create a thread and pass its task number as an argument
        if (pthread_create(&threads[i], NULL, threadTask, &taskNumbers[i]) != 0) {
            fprintf(stderr, "Could not create thread %d\n", taskNumbers[i]);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < numThreads; i++) {
        if (pthread_join(threads[i], &returnValue) != 0) {
            fprintf(stderr, "Could not join thread %d\n", i + 1);
            exit(EXIT_FAILURE);
        }

        // Print the exit status returned by the thread
        printf("Thread %d completed with status %ld\n", i + 1, (long) returnValue);
    }

    printf("All threads have finished their work :)\n");

    pthread_exit((int *) 0);
}
