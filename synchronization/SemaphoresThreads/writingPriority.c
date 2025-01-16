 /* Bakery Shop Analogy
-----------------------

READERS
-------

1) Readers are customers who want to look at the bakery items on display

2) Multiple customers can browse the display cases at the same time without disturbing each other

3) Customers should not browse while the baker is restocking the display, to avoid confusion or errors

WRITERS
--------

1) Writers are bakers who restock the bakery display

2) Only one baker can restock at a time (to avoid chaos)

3) While the baker is restocking, no customers should be browsing the display

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// GLOBAL Semaphores and counters for managing customers and bakers

// Semaphores for synchronization
sem_t *readerSetupMutex, *readerCountMutex, *writerCountMutex, *readerAccess, *writerAccess;
int nr = 0;  // Number of customers reading
int nw = 0;  // Number of bakers writing


// Baker ( Writer ) thread function

static void *baker(void *a){

  int *i = (int *) a; // Baker ID

  // Step 1: Start restocking => Done by the baker => ( block customers )
  sem_wait(writerCountMutex);    // Ensure no other baker modifies the count => Lock
  nw++;                          // A new baker is ready to restock
  if (nw == 1) {
    sem_wait(readerAccess);      // The first baker blocks customers from browsing
  }
  sem_post(writerCountMutex);    // Allow other bakers to proceed


  // Step 2: Restocking display (exclusive access)

  sem_wait(writerAccess);      // Ensure only one baker is restocking
  printf("Baker %d is restocking the display...\n", *i); // Restocking...
  sleep(5);                    // Simulate restocking time
  sem_post(writerAccess);      // Allow another baker to restock if needed


  // Step 3: Finish restocking ( unblock customers )

  sem_wait(writerCountMutex);   // Ensure no other baker is modifying the count
  nw--;                         // This baker is done restocking
  if (nw == 0) {
    sem_post(readerAccess);     // If no more bakers, customers can browse again
  }
  sem_post(writerCountMutex);   // Allow other bakers to proceed

  return NULL; // Exit the thread


}

// Customer (Reader) thread function
static void *customer(void *a) {

  int *i = (int *)a; // Customer ID
  sleep(2);          // Customers arrive after some delay


  // Step 1: Start browsing the display

  sem_wait(readerSetupMutex);       // Ensure only one customer sets up browsing at a time
  sem_wait(readerAccess);           // Ensure no bakers are restocking during setup
  sem_wait(readerCountMutex);       // Protect the customer count

  nr++;                             // A new customer starts browsing
  if (nr == 1) {
    sem_wait(writerAccess);         // The first customer blocks bakers from restocking
  }
  sem_post(readerCountMutex);       // Allow other customers to proceed
  sem_post(readerAccess);           // Allow other customers to proceed
  sem_post(readerSetupMutex);       // Allow other customers to proceed



  // Step 2: Browse the display

  printf("Customer %d is browsing the menu :) \n", *i); // Browsing

  sleep(1);                       // Simulate browsing time


  // Step 3: Finish browsing
  sem_wait(readerCountMutex);     // Protect the customer count
  nr--;                           // This customer is done browsing
  if (nr == 0) {
    sem_post(writerAccess);       // If no more customers, allow bakers to restock
  }
  sem_post(readerCountMutex);     // Allow other customers to proceed

  return NULL; // Exit the thread

}

// Main function to set up the bakery
int main(void) {

  pthread_t thA, thB; // Thread handles for customers and bakers.
  int i, *threadId;   // Iteration variable and pointer for thread IDs.


  // Allocate memory for semaphores and initialize them.
  readerAccess = (sem_t *)malloc(sizeof(sem_t));       // Semaphore to block customers
  writerAccess = (sem_t *)malloc(sizeof(sem_t));       // Semaphore to block bakers
  readerSetupMutex = (sem_t *)malloc(sizeof(sem_t)); // Mutex for customer setup
  readerCountMutex = (sem_t *)malloc(sizeof(sem_t));   // Mutex for customer count
  writerCountMutex = (sem_t *)malloc(sizeof(sem_t));   // Mutex for baker count


  sem_init(readerAccess, 0, 1);       // Initialize 'r' to 1 (customers allowed)
  sem_init(writerAccess, 0, 1);       // Initialize 'w' to 1 (bakers allowed)
  sem_init(readerSetupMutex, 0, 1); // Initialize 'me' to 1 (unlocked)
  sem_init(readerCountMutex, 0, 1);   // Initialize 'me1' to 1 (unlocked)
  sem_init(writerCountMutex, 0, 1);   // Initialize 'me2' to 1 (unlocked)


  setbuf(stdout, 0);    // Disable buffering for output (prints immediately)


  // Create customer threads (10 customers)
  for (i = 0; i < 10; i++) {
    threadId = (int *) malloc (sizeof(int));        // Allocate memory for one integer => (customer ID)
    *threadId = i;                                  // Assign customer ID
    pthread_create(&thA, NULL, customer, threadId); // Start a customer thread
  }

  // Create baker threads (10 bakers)
  for (i = 0; i < 10; i++) {
    threadId = (int *) malloc (sizeof(int));  // Allocate memory for one integer => (for baker ID)
    *threadId = i;                          // Assign baker ID
    sleep(1);                               // Delay to stagger baker creation
    pthread_create(&thB, NULL, baker, threadId); // Start a baker thread
  }

  pthread_exit(0); // Wait for all threads to finish and exit the program

}
