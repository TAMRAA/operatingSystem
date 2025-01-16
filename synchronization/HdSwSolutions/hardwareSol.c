#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define numThreads 5
#define numIterations 10

// Shared resources
int counter = 0;
char lock = false;

// Tracks which thread is waiting to enter the critical section => help prevent starvation
bool waiting[numThreads] = {false};



// Test-And-Set function sets the lock to true and returns the previous value,
// allowing threads to acquire the lock automically

char TestAndSet(char *lock) {
    char val = *lock; // Store the current state of the lock
    *lock = true; // Set the lock
    return val; // Return the old value of the lock
}

// Swap function
void swap(char *v1, char *v2) {
    char tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

// Thread function
void* threadFunction(void* arg) {

    int threadId= * (int *) arg;

    for (int i = 0; i < numIterations; i++) {
        // Implementing mutual exclusion with Test-And-Set

        waiting[threadId] = true;

        // Acquire lock
        while (waiting[threadId] && TestAndSet(&lock));

        // Critical Section
        counter++; // Update shared resource

        fprintf(stdout,"Thread %d => counter %d\n", threadId, counter);
        // End of Critical Section


        // Exit critical section
        waiting[threadId] = false;

        // the thread checks if the lock is released properly and that waiting threads are handled

        // check if it is locked
        if (lock == true) {

            /* Finding the Next Waiting Thread...

               The % NUM_THREADS operator ensures that if j exceeds the number of threads,
               it wraps around to the beginning (circular array behavior)

            */
            int j = (threadId + 1) % numThreads; // This initializes j to the next thread in line

            /* Loop to Find Waiting Threads:

            while (j != thread_id && !waiting[j])

            =>  This loop continues to check for the next waiting thread

            => It will keep incrementing j until it wraps back around to the current thread (j == thread_id)
            meaning it has checked all threads

            => It finds a thread that is waiting (waiting[j] == true).

            */

            while (j != threadId && !waiting[j]) {
                // Find the next waiting thread
                j = (j + 1) % numThreads;
            }

            // After checking all threads => no other thread is waiting to enter the CS
            if (j == threadId) {
                lock = false; // Release the lock if no one is waiting
            }

            // Means a waiting thread was found
            else {
                waiting[j] = false; // Allow the next waiting thread to enter
            }
        }
    }
    return NULL;
}

int main() {

    pthread_t threads[numThreads];
    int threadIds[numThreads];

    // Create threads
    for (int i = 0; i < numThreads; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, &threadIds[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the final value of the counter
    printf("Final counter value: %d :)\n", counter);
    return EXIT_SUCCESS;
}