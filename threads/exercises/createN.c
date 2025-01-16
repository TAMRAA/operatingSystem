#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define numThreads 50

void *threadUtility(void *arg){

  long int tid = (long int) arg;
  sleep(tid);
  fprintf(stdout,"Thread %ld activated :)\n",tid);

  pthread_exit((int *) 0);
}

int main(int argc, char **argv){

  pthread_t threads[numThreads];
  int status;

  fprintf(stdout,"Welcome to my app ❤️\n");
  int n = atoi(argv[1]);

  for(int i = 0; i < n; i++){
    fprintf(stdout,"Creating thread %d...\n", i+1);
    status = pthread_create(&threads[i], NULL, threadUtility, (void *) i + 1);
    if(status){
      fprintf(stderr,"Error Threading\n");
      exit(1);
    }
  }

  pthread_exit((int *) 0);
}