/*

Creates two threads, one printing 10 "a"s, the other printing 10 "b"s

   Illustrates
   1) thread creation,
   2) thread joining
   3) status and retvalue
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pthread.h"

// global variable
int global = 10;

static void *threadUtility (void *arg){

  // cast the void argument to the real type
  char *c = (char *) arg;
  int i;

  fprintf (stderr, "\nStarting thread %s, global = %d\n", c, global);

  for (i = 0; i < 10; i++){
    // directly writes data to a file descriptor
    write (1, c, 1);
  }
  fprintf(stdout,"\n");
  return  c;
}

int main (void){

    pthread_t thread1, thread2;
    int status;
    void *retval;

    status = pthread_create (&thread1, NULL, threadUtility, (void *) "a");
    if (status){
        fprintf (stderr, "Thread 1 failure with status = %d :(\n", status);
    }

    status = pthread_create (&thread2, NULL, threadUtility, (void *) "b");
    if (status){
        fprintf (stderr, "Thread 2 failure with status = %d :(\n", status);
    }


    status = pthread_join (thread1, &retval);
    fprintf(stderr, "retval => %c\n",   * (char *) retval);

    if (status){
        fprintf (stderr, "A failed to join => status = %d\n", status);
    }

    status = pthread_join (thread2, &retval);

    fprintf(stderr, "retval => %c\n",   * (char *) retval);

    if (status){
        fprintf (stderr, "B failed to join => status = %d\n", status);
    }

    return EXIT_SUCCESS;

}
