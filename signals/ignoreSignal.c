#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#define deltaT 2

int main (int argc,char **argv){
  
  int ret, code;

  if(argc > 1){
    signal(SIGCHLD, SIG_IGN);
  }

  for(int i = 1; i < 6 ; i++){
    if(!fork()){
      sleep(i * deltaT);
      fprintf(stdout,"I am Child #%d with PID %d and i slept for %d seconds\n", i, getpid(), i*deltaT);
      exit(i);
    }
  }

  // Ensure that child processes are finished!
  sleep(5);
  ret = wait(&code);
  fprintf(stdout,"Returned values => ret = %d and code = %d\n", ret, code);
  return EXIT_SUCCESS;
}


