#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    // Check for the correct number of command line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_elements>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n, retValue;
    int *array;
    pid_t pid;

    n = atoi(argv[1]);  // Convert input argument to an integer
    array = (int *) malloc(n * sizeof(int));
    
    // Check for memory allocation failure
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed :(\n");
        exit(EXIT_FAILURE);
    }

    // Input array elements
    fprintf(stdout, "Input:\n");
    for (int i = 0; i < n; i++) {
        fprintf(stdout, "vet[%d]: ", i);
        scanf("%d", &array[i]);
    }

    // Output process creation
    fprintf(stdout, "Output:\n");
    for (int i = 0; i < n; i++) { // Corrected loop to run n times
        
        pid = fork();
        if (pid < 0) {
            // Handle fork failure
            perror("Fork failed");
            free(array); // Free allocated memory before exiting
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Child process
            fprintf(stdout, "Run PID=%d, vet[%d]: %d\n", getpid(), i, array[i]);
            exit(EXIT_SUCCESS); // Ensure child exits after printing
        } else { // Parent process
            wait(&retValue); // Wait for the child to finish
        }
    }

    // Cleanup
    free(array); // Free allocated memory

    fprintf(stdout, "End PID=%d\n", getpid());
    
    exit(EXIT_SUCCESS);
}
