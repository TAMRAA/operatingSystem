/*
  The producer-consumer problem involves two types of processes:
  1) Producers => which generate data and place it into a buffer
  2) Consumers => which take data from the buffer

  The goal is to ensure that producers don't attempt to add data when the buffer is full,
  and consumers don't try to remove data when the buffer is empty
*/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 16
#define OVER (-1)


typedef struct{

  // A count that tracks available resources
  int count;

  // A lock mutex to protect access to the semaphore state
  pthread_mutex_t lock;

  // Another lock mutex S that blocks threads when resources are unavailable
  pthread_mutex_t block;

}Semaphore;


Semaphore *check, *available;
int in, out;
int buffer[BUFFER_SIZE];

// Initialize a semaphore
static void semaphore_init (Semaphore *s, int i) {

  pthread_mutex_init (&s->lock, NULL);
  pthread_mutex_init (&s->block, NULL);
  pthread_mutex_lock(&s->block);

  s->count = i;
}

static void semaphore_wait (Semaphore *s) {

  pthread_mutex_lock (&s->lock);
  s->count--;

  if (s->count < 0){
  	pthread_mutex_unlock (&s->lock);
    pthread_mutex_lock (&s->block);
  }

  else{
    pthread_mutex_unlock (&s->lock);
  }

}

static void semaphore_signal (Semaphore *s) {

  pthread_mutex_lock (&s->lock);

  s->count++;

  if (s->count <= 0){
    pthread_mutex_unlock (&s->block);
  }

  pthread_mutex_unlock (&s->lock);

}


/* Store an integer in the buffer */
static void set (int data) {

  semaphore_wait(available);

  buffer[in] = data;
  in = (in + 1) % BUFFER_SIZE;

  semaphore_signal(check);

}

/* Read and remove an integer from the buffer */
static int get (void){

  int data;

  semaphore_wait(check);

  data = buffer[out];
  out = (out + 1) % BUFFER_SIZE;

  semaphore_signal(available);

  return data;
}

/* A test program: one thread inserts integers from 1 to 10000,
   the other reads them and prints them. */

static void *producer (void *data)
{
  int n;

  for (n = 0; n < 10000; n++) {
      printf ("%d --->\n", n);
      set (n);
  }

  set (OVER);

  return NULL;
}

static void *consumer (void *data)
{
  int d;
  while (1){
    d = get();
      if (d == OVER){
        break;
      }
      printf ("<--- %d\n", d);
  }
  return NULL;
}

int main (void){

  pthread_t th_a, th_b;
  void *retval;

  available = (Semaphore *) malloc(sizeof(Semaphore));
  check = (Semaphore *) malloc(sizeof(Semaphore));

  semaphore_init (available, BUFFER_SIZE);
  semaphore_init (check, 0);

  in = 0;
  out = 0;

  /* Create the threads */
  pthread_create (&th_a, NULL, producer, 0);
  pthread_create (&th_b, NULL, consumer, 0);

  /* Wait until producer and consumer finish. */
  pthread_join (th_a, &retval);
  pthread_join (th_b, &retval);

  for(int i = 3; i > 0; i--) {
    fprintf(stdout, "App is closing in %d seconds...\r", i);
    fflush(stdout);
    sleep(1);
  }

  fprintf(stdout, "Thanks for using my App <3, Hope you like it :)\n");

  return EXIT_SUCCESS;
}
