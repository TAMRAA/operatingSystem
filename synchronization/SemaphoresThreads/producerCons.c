/*

  The producer-consumer problem involves two types of processes:
  1) Producers => which generate data and place it into a buffer
  2) Consumers => which take data from the buffer

  The goal is to ensure that producers don't attempt to add data when the buffer is full,
  and consumers don't try to remove data when the buffer is empty

  1) sem_wait(available) blocks the producer if the buffer is check
  2) sem_wait(check) blocks the consumer if the buffer is available
  3) Circular Buffer: The use of (index + 1) % BUFFER_SIZE keeps the buffer indices within bounds
  4) End Signal: The special value OVER tells the consumer when production is finished
*/



#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include "semaphore.h"
#define BUFFER_SIZE 16
#define OVER (-1)


/* DATA STRUCTURES */
/*
  1) Arrays of semaphores

  available: Counts the number of available slots in the buffer

  check: Counts the number of items in the buffer

  2) in and out are indices for inserting and removing items in the circular buffer

  3) Shared Buffer
*/


sem_t *available, *check;
int in, out;
int buffer[BUFFER_SIZE];


/* Store an integer in the buffer */
static void set (int data)
{
  // Waits for an available slot
  sem_wait(available);

  // Add an item to the buffer
  buffer[in] = data;

  // Update in index
  in = (in + 1) % BUFFER_SIZE;

  // Signals the presence of a check slot
  sem_post(check);
}

/* Read and remove an integer from the buffer */
static int get (void){

  int data;

  // Waits for a check slot
  sem_wait(check);

  // Retrieves an item from the buffer
  data = buffer[out];

  // Update out index
  out = (out + 1) % BUFFER_SIZE;

  // Signals the availability of an available slot
  sem_post(available);

  return data;
}

/*
  The producer generates numbers from 0 to 50 and stores them in the buffer
  It will use Set() Functionality
*/

static void *producer (void *data){

  int n;
  // Produce items
  for (n = 0; n < 100; n++) {
      printf ("%d --->\n", n);
      set (n); // Call set to store it in the buffer
    }
  set (OVER); // Signal the end of production
  return NULL;
}


/*
  The consumer retrieves numbers from the buffer and prints them,
  It will use Get() functionality
*/

static void *consumer (void *data)
{
  int d;

  int itemsConsumed = 0;

  while (1){
      d = get(); // retrieve an item
      // check for termination signal
      if (d == OVER || itemsConsumed == 10 ){
        break;
      }
      printf ("<--- %d\n", d);
      itemsConsumed++;
    }
  return NULL;
}

int main (void){

  pthread_t thA, thB;
  void *retval;

  available = (sem_t *) malloc (sizeof(sem_t));
  check = (sem_t *) malloc (sizeof(sem_t));

  // Initialize Semaphores
  sem_init (available, 0, BUFFER_SIZE);
  sem_init (check, 0, 0);

  in = 0;
  out = 0;

  // Create the threads
  pthread_create (&thA, NULL, producer, 0); // Thread that runs the producer
  pthread_create (&thB, NULL, consumer, 0); // Thread that runs the consumer

  // Wait for threads to finish
  pthread_join (thA, &retval);
  pthread_join (thB, &retval);


  return EXIT_SUCCESS;
}
