// Generation of n children process
// Before any fork() calls, there is the parent process that is already running
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int i, n;

  n = atoi(argv[1]);

  // Each call to fork() doubles the number of processes
  // For n iterations, it creates (2^n) processes
  for (i = 0; i < n; i++) {
    fork();
    printf ("I am Process %d with PID=%d)\n", i, getpid());
  }

  return 0;
}
