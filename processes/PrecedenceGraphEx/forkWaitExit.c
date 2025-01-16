/*
 *  Illustrates fork, wait, and exit return information
 *  Once run: Use
 *  echo $?
 *  to make the shell print out the parent return value (25)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void){
  pid_t pid, childPid;
  int status;

  pid = fork();
    
  if(pid > 0){
    fprintf(stdout,"Parent Process\n");
    fprintf(stdout,"Pid: %d\n", getpid());
    fprintf(stdout,"Parent Pid: %d\n", getppid());
    fprintf(stdout,"Child Pid: %d\n\n", pid);

    // Wait for Child Process to finish
    childPid = wait(&status);

    // Display informations of child process
    fprintf(stdout,"Child Informations\n");
    fprintf(stdout,"Child Pid Version 1: %d\n", childPid);
    fprintf(stdout,"Child Pid Version 2: %d\n", pid);
    fprintf(stdout,"Parent Pid: %d\n", getpid());

    fprintf(stdout,"WIFEEXITED = %d\n",WIFEXITED(status));
    fprintf(stdout,"WEXITSTATUS = %d\n\n",WEXITSTATUS(status));


  }else if(pid == 0){

    fprintf(stdout,"Child Process\n");
    fprintf(stdout,"Pid: %d\n", getpid());
    fprintf(stdout,"Parent Pid: %d\n", getppid());
    fprintf(stdout,"Child Pid: %d\n\n", pid);
    exit(6);

  }else{
    fprintf(stdout,"Forking failed :(\n");
    exit(1);
  }

  return 0;
}
