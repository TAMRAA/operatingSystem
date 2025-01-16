#include <stdio.h>
#include <pthread.h>

// Function that will be executed by the threads
void *printMessage (void *arg) {
    char *message = (char *) arg;
    printf("%s\n", message);
    pthread_exit((int *) 0); // Properly exits the thread
}

int main() {

    pthread_t thread1, thread2;

    // Creating the first thread
    if (pthread_create(&thread1, NULL, printMessage, "Hello from Thread 1") != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }
    
    // Creating the second thread
    if (pthread_create(&thread2, NULL, printMessage, "Hello from Thread 2") != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Waiting for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads finished executing :)\n");

    return 0;
}
