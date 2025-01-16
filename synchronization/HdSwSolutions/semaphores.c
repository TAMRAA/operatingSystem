#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <pthread.h>
#include <semaphore.h>
#define numThreads 5

sem_t semahore;

// Global var
int counter = 0;


void *threadUtility(void *arg){
  int threadId = *(int *) arg;

  sem_wait(&semahore);

  // Accessing critical area
  counter++;
  fprintf(stdout,"Thread %d => counter = %d\n", threadId, counter);

  sem_post(&semahore);
  pthread_exit((int *) 0);
}

int main(int argc, char **argv){

  pthread_t threads[numThreads];
  int threadIds[numThreads];
  int status;

  fprintf(stdout,"Welcome to my app :)\n");

  sem_init(&semahore, 0 , 1);

  for(int i = 0; i < numThreads; i++){
    fprintf(stdout,"Creating thread %d\n", i);
    threadIds[i] = i;
    status = pthread_create(&threads[i], NULL, threadUtility, &threadIds[i]);
  }

  sem_destroy(&semahore);
  pthread_exit((int *) 0);
}