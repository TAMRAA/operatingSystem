#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define numThreads 8

sem_t semEmpty, semFull;
pthread_mutex_t mutexBuffer;

// Global Variables
int buffer[10];
int count = 0;


static void *consumer(void *args){


  return NULL;
}

static void *producer(void *args){


  return NULL;
}



int main(void){

  pthread_t threads[numThreads];
  int status, *threadIDs[numThreads];

  sem_init(&semEmpty, 0, 10);
  sem_init(&semFull, 0, 0);
  


  for(int i = 0; i < numThreads; i++){
    if(i > 0){
      *threadIDs[i] = i;
      status = pthread_create(&threads[i], NULL, consumer, &threadIDs[i]);
      if(status){
        fprintf(stderr,"Threading 404\n");
        exit(0);
      }
    }else{
      *threadIDs[i] = i;
      status = pthread_create(&threads[i], NULL, producer, &threadIDs[i]);
      if(status){
        fprintf(stderr,"Threading 404\n");
        exit(0);
      }
    }
  }

  for(int i = 0; i < numThreads ; i++){
    status = pthread_join(threads[i], NULL);
    if(status){
      fprintf(stderr,"Threading 404\n");
      exit(0);
    }
  }

  return 0;
}