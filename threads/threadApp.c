#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>

#define NUM_THREADS 3

// Global variable accessible to all threads
int globalVariable = 10;

// Mutex and condition variables
pthread_mutex_t mutex;
pthread_cond_t cond_var;
int turn = 0;

// Thread data structure
typedef struct {
    int thread_num;  // Unique ID for the thread
    char letter;
} myThread;

// Function prototypes
static void *process(void *arg);

int main(void) {
    // Array to hold thread identifiers
    pthread_t th[NUM_THREADS];

    // Array of threads data structure
    myThread threadStructure[NUM_THREADS];

    char *retvalue;  // from threads
    int retcode;   // check success of pthread functions
    int i;


    // Initialize the threads
    for (i = 0; i < NUM_THREADS; i++) {
        threadStructure[i].letter = 'a' + i;  // Assign letters 'a', 'b', 'c' to threads
    }

    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        threadStructure[i].thread_num = i;  // Assign thread number
        retcode = pthread_create(&th[i], NULL, process, (void *) &threadStructure[i]); // Pass thread data to process()
        if (retcode != 0) {
            fprintf(stderr, "pthread_create failed with code %d\n", retcode);
        }
    }

    // Wait for threads to complete
    for (i = 0; i < NUM_THREADS; i++) {
        retcode = pthread_join(th[i], (void *)&retvalue);  // Wait for the thread and retrieve its return value
        if (retcode != 0) {
            fprintf(stderr, "pthread_join failed with code %d\n", retcode);
        } else {
            // Print the value returned by the thread
            fprintf(stdout, "Thread %d returned value: %c\n", i, *retvalue);
        }
    }

    fprintf(stdout, "Final value of globalVariable: %d\n", globalVariable);


    return 0;
}

// Function executed by each thread
static void *process(void *arg) {
    int i;
    myThread *param = (myThread *)arg;

    // Example of modifying a global variable
    if (param->thread_num == 0) {
        globalVariable = 20;  // Only thread 0 changes the global variable
    }

    // Print thread-specific information
    fprintf(stdout, "Thread %d started: letter=%c, globalVariable=%d\n", param->thread_num, param->letter, globalVariable);



    // Perform some work: Print the thread's letter 10 times
    for (i = 0; i < 10; i++) {
        write(STDOUT_FILENO, &(param->letter), 1);  // Write letter to stdout
        write(STDOUT_FILENO, "\n", 1);             // Newline for readability
    }

    // Convert the thread's letter to uppercase as the return value
    param->letter = toupper(param->letter);

    // Exit the thread and return the modified letter
    pthread_exit(&(param->letter));
}