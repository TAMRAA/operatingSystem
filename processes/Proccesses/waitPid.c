#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


// The waitpid allows a parent process to wait for changes in the state of a child process
pid_t waitpid(pid_t pid, int *statLoc, int options);

/*

  ARGUMENTS
  ---------

  [pid]:      Specifies which process to wait
  [statLoc]:  Pointer to an integer where the exit status of the child process will be stored
  [options]:  Flags that modify the behavior of waitpid (e.g., WNOHANG to return immediately if no child has exited)


  pid Parameter Values
  ---------------------
  pid = -1: Wait for any child process => (equivalent to wait())

  pid > 0: Wait for the specific child process with PID = pid

  pid = 0: Wait for any child process in the same process group as the calling process
*/

int main() {

    pid_t pid1, pid2, pid3;
    int status;


    pid1 = fork();

    // Child 1
    if (pid1 == 0){

        printf("Child 1 (PID: %d)\n", getpid());
        sleep(2);
        exit(1);
    }

    pid2 = fork();
     // Child 2
    if (pid2 == 0){

        printf("Child 2 (PID: %d)\n", getpid());
        sleep(4);
        exit(2);
    }

    pid3 = fork();

    // Child 3
    if (pid3 == 0) {

        printf("Child 3 (PID: %d)\n", getpid());
        sleep(6);
        exit(3);
    }

    // Waiting for any child process (equivalent to wait)
    pid_t waited_pid = waitpid(-1, &status, 0);
    if (waited_pid > 0) {
        printf("Child with pid [%d] finished :)\n", waited_pid, WEXITSTATUS(status));
    }

    // Waiting for a specific child process with PID = pid2
    waited_pid = waitpid(pid2, &status, 0);
    if (waited_pid > 0) {
        printf("Child with pid [%d] finished :)\n", waited_pid, WEXITSTATUS(status));
    }

    // Waiting for any child process with the same GID as the parent
    waited_pid = waitpid(0, &status, 0);
    if (waited_pid > 0) {
        printf("Child with pid [%d] finished :)\n", waited_pid, WEXITSTATUS(status));
    }

    // Waiting for any child in a specific group (use -getpgid(pid3) for this example)
    waited_pid = waitpid(-getpgid(pid3), &status, 0);
    if (waited_pid > 0) {
        printf("Child with pid [%d] finished :)\n", getpgid(pid3), waited_pid, WEXITSTATUS(status));
    }
    return 0;
}
