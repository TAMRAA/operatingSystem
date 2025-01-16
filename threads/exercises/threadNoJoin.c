#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


/*
  Thread detachment
  -----------------
  In the context of POSIX threads (pthreads) refers to the process of making a thread run independently
  such that when it finishes execution, its resources are automatically released without requiring the
  parent thread to explicitly join it
*/


// Global vars
int one = 1, two = 2;


void abortMission(int status, char *message){
  fprintf(stderr,"%s with status = %d\n", message, status);
}

static void *printThread(void *args){

  int *t = (int *) args;
  int status;

  status = pthread_detach(pthread_self());
  if(status){
    abortMission(status,"Error detaching thread...\n");
  }

  for(int i = 0; i <= 5 ; i++){
    system("date");
    fprintf(stdout,"i = %d => I am Thread %d :)\n\n", i, *t);
    sleep(1);
  }

  pthread_exit(NULL);

}

int main(int argc, char **argv){

  pthread_t thread;
  int status;

  // Pass Global Var One
  status = pthread_create(&thread, NULL, printThread, &one);

  if(status){
    abortMission(status, "Error creating thread one :X\n");
  }

  // Pass Global Var Two
  status = pthread_create(&thread, NULL, printThread, &two);
  if(status){
    abortMission(status, "Error creating thread two :X\n");
  }

  pthread_exit((int *) 0);

}
