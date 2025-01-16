#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

// Define a buffer size
#define BUFFER_SIZE 1024 

int main() {
    const char *filePath = "example.txt"; // File to read from
    char buffer[BUFFER_SIZE]; // Buffer to hold the read data

    // Open the file for reading
    int fd = open(filePath, O_RDONLY);
    
    // Check if the file opened successfully
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read from the file
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    
    // Check if the read was successful
    if (bytesRead == -1) {
        perror("Error reading from file");
        close(fd); // Close the file descriptor before exiting
        exit(EXIT_FAILURE);
    }

    // Null-terminate the buffer to make it a valid string
    buffer[bytesRead] = '\0';

    // Print the read data to the standard output
    printf("Read %zd bytes:\n%s", bytesRead, buffer);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    return 0;
}