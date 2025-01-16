#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#define N 20


int main(int argc, char **argv) {

  sem_t sem1, sem2;
  void *forking;

  setbuf (stdout, 0);

  // sem1 is shared between processes and it it available for use
  sem_init (&sem1, 1, 1);

  // sem2 is shared between processes and it's not available for now
  sem_init (&sem2, 1, 0);

  forking = fork();
  // Parent
  if (forking) {

    for (int i = 0; i < N; i++) {
      sem_wait (&sem1);
      fprintf (stdout, "Parent %d\n", i);
      sem_post (&sem2);
    }
    wait (NULL);

  }
  // child
  else if(!forking){

    for (int i=0; i < N; i++) {
      sem_wait (&sem2);
      fprintf (stdout, "Child %d\n", i);
      sem_post (&sem1);
    }

  }else{
    fprintf(stderr,"Forking 404\n");
    exit(1);
  }

  sem_destroy (&sem1);
  sem_destroy (&sem2);

  fprintf (stdout, "Bye\n");
  return 0;
}