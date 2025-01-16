/*
 * Implements a precedence graph
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "pthread.h"

/* generates a random integer between 1 and the given maximum value max */
int random_time(int max){
  return (int)(rand() % max) + 1;
}

static void *CF (void *arg) {
  int *t = (int *) arg;
  int rt;

  sleep (*t);
  printf ( "C after %d seconds\n", *t);
  rt = random_time (2);
  sleep (rt);
  printf ( "F after %d seconds\n", *t);

  return  0;
}

static void *E (void *arg) {
  int *t = (int *) arg;

  sleep (*t);
  printf ( "E after %d seconds\n", *t);

  return  0;
}

int main (void) {
  pthread_t th_cf, th_e;
  int *rt;
  void *retval;

  srand (getpid());
  rt = (int *) malloc (sizeof (int));

  *rt = random_time (10);
  sleep (*rt);
  printf ("A after %d seconds\n", *rt);

  *rt = random_time (10);
  pthread_create (&th_cf, NULL, CF, (void *) rt);

  *rt = random_time (5);
  sleep (*rt);
  printf ("B after %d seconds\n", *rt);

  *rt = random_time (10);
  pthread_create (&th_e, NULL, E, (void *) rt);

  *rt = random_time (5);
  sleep (*rt);
  printf ("D after %d seconds\n", *rt);

  pthread_join (th_cf, &retval);
  pthread_join (th_e, &retval);

  *rt = random_time (8);
  sleep (*rt);
  printf ("G after %d seconds\n", *rt);

  return 0;
}