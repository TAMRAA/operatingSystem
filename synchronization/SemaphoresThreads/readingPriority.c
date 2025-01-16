#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t *readerCountMutex, *mixAccess, *writerSetupMutex;
int activeReader = 0;

/*
Global Semaphores and counters for managing readers and writers
................................................................
  1. readerCountMutex: Protects the count of active readers
  2. mixAccess: Controls access to the shared resource, allowing either multiple readers or one writer
  3. writerSetupMutex: Ensures that writers set up sequentially without conflicts
*/



// Thread Utilities
static void *baker(void *a);
static void *customer(void *a);


// Main function
int main(void) {

  pthread_t threadA, threadB;
  int i, *threadId;

  // Allocate memory for semaphores and initialize them
  mixAccess     = (sem_t *) malloc (sizeof(sem_t));
  readerCountMutex = (sem_t *) malloc (sizeof(sem_t));
  writerSetupMutex = (sem_t *) malloc (sizeof(sem_t));

  sem_init(mixAccess, 0, 1);       // Initialize to 1 (writers allowed)
  sem_init(readerCountMutex, 0, 1);   // Initialize to 1 (unlocked)
  sem_init(writerSetupMutex, 0, 1);   // Initialize to 1 (unlocked)

  setbuf(stdout, 0); // Disabling output buffering for immediate prints

  /* 10 Customers */
  for (i = 0; i < 10; i++) {
    threadId = (int *) malloc (sizeof(int));
    *threadId = i;                           // Assign reader ID
    pthread_create(&threadA, NULL, customer, threadId);
  }

  /* 10 Bakers */
  for (i = 0; i < 10; i++) {
    threadId = (int *)malloc(sizeof(int));
    *threadId = i;                           // Assign writer ID
    pthread_create(&threadB, NULL, baker, threadId);
  }

  pthread_exit(0);
}



// Threads utilities decalarations

/* Writer Thread utility */
static void *baker(void *a) {

  int *threadId = (int *)a;

  // Step 1: Prepare to write (exclusive access)
  sem_wait(writerSetupMutex);  // Ensure no writer setup conflicts
  sem_wait(mixAccess);      // Block readers and other writers

  printf("Baker %d is writing...\n", *threadId);


  sem_post(mixAccess);      // Allow readers or another writer to proceed
  sem_post(writerSetupMutex);  // Allow another writer to setup

  phtread_exit(0);
}

/* Reader thread utility => ( HIGH PRIORITY HERE ) */
static void *customer(void *a) {

  int *threadId = (int *)a;
  sleep(1);

  // Step 1: Start reading (shared access among readers)
  sem_wait(readerCountMutex);  // Protect the reader count => Increment the active readers count
  if(activeReader == 1) {
    sem_wait(mixAccess);    // First reader blocks writers
  }
  sem_post(readerCountMutex);  // Allow other readers to proceed

  // Step 2: Reading the shared resource
  printf("Customer %d is reading :)\n", *threadId); // Reading

  // Step 3: Finish reading
  sem_wait(readerCountMutex);  // Protect the reader count => Decrement the active readers count
  if(activeReader == 0) {
    sem_post(mixAccess);    // Last reader unblocks writers
  }
  sem_post(readerCountMutex);  // Allow other readers to proceed

  phtread_exit(0);
}
