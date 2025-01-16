#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void){

    // Define the file name
    const char *filePath = "example.txt";

    // Open the file for writing; create it if it doesn't exist
    int fileDescriptor = open(filePath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    // Check if the file opened successfully
    if (fileDescriptor == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write to the file
    const char *text = "Hello, this is a sample text written to the file.\n";
    ssize_t bytesWritten = write(fileDescriptor, text, strlen(text));

    // Check if the write was successful
    if (bytesWritten == -1) {
        perror("Error writing to file");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fileDescriptor) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    printf("File '%s' created and text written successfully.\n", filePath);
    return 0;
}
