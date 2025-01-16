#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){

  pid_t pid, childpid;
  int returnValue;

  pid = fork();

  if(pid){

    // Parent process
    fprintf(stdout, "Parent process (PID = %d) waiting for child to terminate ...\n", getpid());

      // Retrieves the child's exit status
      childpid = wait(&returnValue);

      if (childpid > 0) {

        fprintf(stdout,"Child terminated: PID = %d\n", childpid);
        // Check if the child terminated normally
        if (WIFEXITED(returnValue)) {
          // Print child's exit code
          fprintf(stdout,"Exit value: %d\n", WEXITSTATUS(returnValue));
        }
        else {
          fprintf(stdout,"Abnormal termination\n");
        }
      }
      else {
          perror("wait");  // Error handling in case wait fails
      }
  }else{
      // Child process
      fprintf(stdout, "Child process started (PID = %d)\n", getpid());
      // Simulate some work in the child process
      sleep(5);
      // Exit with a specific code
      exit(6);
  }

  return 0;
}
