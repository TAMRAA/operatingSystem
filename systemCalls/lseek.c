#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


// CREATE AN APP THAT CREATES A FILE WITH A MESSAGE + LSEEK THE MESSAGE
int main() {


    const char *filePath = "example.txt";
    const char *text = "Hello, this is a simple example of using lseek.\n";


    int fd = open(filePath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }


    write(fd, text, strlen(text));

    close(fd);


    fd = open(filePath, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    // Use lseek to read from the beginning of the file

    char buffer[50];
    lseek(fd, 0, SEEK_SET); // Move the pointer to the beginning
    read(fd, buffer, sizeof(buffer) - 1);
    buffer[49] = '\0';
    printf("Content from offset 0 => \n%s", buffer);


    // Use lseek to read from a specific position (offset 10)
    lseek(fd, 10, SEEK_SET); // Move to 10 bytes from the start
    read(fd, buffer, sizeof(buffer) - 1);
    buffer[49] = '\0';
    printf("Content from offset 10 => \n%s", buffer);



    lseek(fd, -20, SEEK_END);
    read(fd, buffer, sizeof(buffer) - 1);
    buffer[49] = '\0';
    printf("Content from -20 bytes => \n%s", buffer);

    close(fd);
    return 0;
}
