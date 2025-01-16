/*
  Exercise about pthread_create

  To compile: gcc -Wall -o app create.c -lpthread
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *PrintHello () {

  pthread_t tid;
  tid = pthread_self ();

  sleep (2);

  fprintf (stdout, "Thread activated with tid = %d\n", (unsigned int) tid);
  pthread_exit ((int *) 0);
}


int main (int argc, char **argv){

  pthread_t tid;
  int returnCode;

  tid = pthread_self();

  fprintf (stdout, "Main thread created with tid = %d\n", (unsigned int) tid);

  printf (stdout, "Creating thread 1...\n");
  returnCode = pthread_create (&tid, NULL, PrintHello, NULL);

  if (returnCode) {
    fprintf (stderr, "Pthread create 404 %d\n", returnCode);
    exit(-1);
  }

  // Check this out: Enable one of the two
  if (argc > 1) {
    return (0);
  } else {
    pthread_exit (NULL);
  }
}