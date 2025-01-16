#include <stdio.h>
#include <unistd.h>

int main() {

    int n;
    n = 0;

    // While loop, which continues as long as n < 3 and fork() returns non-zero (the parent process)
    while (n < 3 && fork()) {
        
        // Inner `if` block: Only executes for child processes created by the inner `fork()`
        if (!fork()) {
            // Attempt to call `execlp` to execute `echo` with arguments
            execlp("echo", "echo", "n++", "n", NULL);
        }

        // This line won't be reached if `execlp` is successful because `execlp` replaces the process
        n++;
        
        // Prints the value of `n` in the parent process
        fprintf(stdout, "%d\n", n);
    }

    return 1;
}
