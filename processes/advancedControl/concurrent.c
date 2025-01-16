#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

    char *Path = "/Users/tamra/Desktop/Directories/processes/advancedControl/app";
    int n;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    n = atoi(argv[1]);

    switch (n) {
        case 1:
            fprintf(stdout, "PID = %d  PPID = %d\n", getpid(), getppid());
            sleep(n * 2);
            if (execlp(Path, "app", "2", NULL) == -1) {
                perror("execlp failed");
                exit(EXIT_FAILURE);
            }
            break;

        case 2:
            fprintf(stdout, "PID = %d  PPID = %d\n", getpid(), getppid());
            sleep(n * 3);
            if (execlp(Path, "app", "3", NULL) == -1) {
                perror("execlp failed");
                exit(EXIT_FAILURE);
            }
            break;

        default:
            fprintf(stdout, "PID = %d  PPID = %d\n", getpid(), getppid());
            break;
    }

    return EXIT_SUCCESS;
}
