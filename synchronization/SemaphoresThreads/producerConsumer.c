#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

/*
  This code is an implementation of the readers writers problem using POSIX threads (pthread) and semaphores in C.
  It manages concurrent access to a shared resource (baker's goods) by multiple reader threads (customers)
  and writer threads (bakers) while ensuring data consistency and avoiding race conditions
*/

sem_t *singleThreadAccess, *readerCountMutex, *readerAccess, *writerAccess, *writerCountMutex;
int nW = 0;
int nR = 0;

/* singleThreadAccess => is used to ensure that only one reader thread can perform the setup phase at a time */

// Writer thread
static void *baker(void *a){

  // Baker ID
  int *threadID = (int *) a;


  sem_wait(writerCountMutex);
  nW++;
  if(nW == 1){
    sem_wait(readerAccess);
  }
  sem_post(writerCountMutex);

  // Display

  sem_wait(writerCountMutex);
  fprintf(stdout,"Baker %d is updating the menu...\n", *threadID);
  sleep(2);
  sem_post(writerCountMutex);


  // Finish
  sem_wait(writerCountMutex);
  nW--;
  if(nW == 0){
    sem_post(readerAccess);
  }
  sem_post(readerCountMutex);

  return NULL;
}

// Reader
static void *consumer(void *a){

  // Consumer ID
  int *threadID = (int *) a;
  sleep(2);

  // Lock
  sem_wait(readerAccess);
  sem_wait(readerCountMutex);

  /* Lock to prevent multi-threads access, only one thread at a time */
  sem_wait(singleThreadAccess);
  nR++;
  if(nR == 1){
    sem_wait(writerAccess);
  }
  // Unlock
  sem_post(singleThreadAccess);
  sem_post(readerCountMutex);
  sem_post(readerAccess);


  // Display
  fprintf(stdout,"Customer %d is browsing the menu :)\n", *threadID);
  sleep(2);

  // Finish
  sem_post(readerCountMutex);
  nR--;
  if(nR == 0){
    sem_post(writerAccess);
  }
  sem_post(readerCountMutex);

  return NULL;
}

int main(void){

  pthread_t threadA, threadB;
  int i, *threadId;

  singleThreadAccess = (sem_t *) malloc (sizeof(sem_t));
  readerCountMutex = (sem_t *) malloc (sizeof(sem_t));
  readerAccess = (sem_t *) malloc (sizeof(sem_t));
  writerAccess = (sem_t *) malloc (sizeof(sem_t));
  writerCountMutex = (sem_t *) malloc (sizeof(sem_t));

  // 1 => Unlocked
  sem_init(singleThreadAccess, 0 , 1);
  sem_init(readerCountMutex,0, 1);
  sem_init(readerAccess, 0 , 1);
  sem_init(writerAccess, 0, 1);
  sem_init(writerCountMutex, 0, 1);

  /* Baker */
  for(i = 0; i < 10; i++){
    threadId = (int *) malloc (sizeof(int));
    *threadId = i;
    pthread_create(&threadA, NULL, baker, threadId);
  }

  /* Consumer */
  for(i = 0; i < 10; i++){
    threadId = (int *) malloc (sizeof(int));
    *threadId = i;
    sleep(1);
    pthread_create(&threadB, NULL, consumer, threadId);
  }

  pthread_exit(0);
}