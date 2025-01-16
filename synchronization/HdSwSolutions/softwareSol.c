#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define numIterations 10

/*
    This is software solution on how to update counter using threads :)
*/


// Shared Variables
bool flag[2] = {false, false};
int counter = 0;
int turn;

void *threadFunction(void *args){

    int threadID = * (int *) args;

    for(int i = 0; i < numIterations; i++){

        // Enter critical section
        flag[threadID] = true;

            turn = 1 - threadID;

            /* This is the spin lock mechanism */
            // The while loop checks if the other thread wants to enter the CS and waits if it does
            while (flag[1 - threadID] && turn == 1 - threadID);

            // Critical Section
            counter++;

            fprintf(stdout,"Thread %d => counter = %d\n", threadID, counter);

        flag[threadID] = false;

        // End of CS
    }

    pthread_exit(NULL);
}



int main(void){

    pthread_t threads[2];
    int threadIds[2] = {0,1};

    pthread_create(&threads[0], NULL, threadFunction, &threadIds[0]);
    pthread_create(&threads[1], NULL, threadFunction, &threadIds[1]);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    fprintf(stdout, "Final counter value = %d :)\n", counter);

    return EXIT_SUCCESS;
}
