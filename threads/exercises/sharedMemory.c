#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Shared memory app


int global = 0;

// Function signatures
void *threadUtility(void * arg);



// Protection block
pthread_mutex_t lock;

int main(int argc, char **argv){

  pthread_t threadUtil;
  int n, local;

  fprintf(stdout,"Welcome to my app ❤️\n");

  n = atoi(argv[1]);
  pthread_mutex_init(&lock, NULL);

  if(pthread_create(&threadUtil, NULL, threadUtility, (void *) n) != 0){
    fprintf(stderr,"Error creating Thread");
    exit(404);
  }

  for(int i = 0; i < n; i++){

    pthread_mutex_lock(&lock);

    local = global;
    local++;
    global = local;
    fprintf(stdout,"Main thread => Global = %d\n", global);

    pthread_mutex_unlock(&lock);

    sleep(1);
  }

  fprintf(stdout,"⚡️ Final Result from Main Thread => Global = %d ⚡️\n", global);

  return 0;
}

void *threadUtility(void * arg){

  int n = (intptr_t) arg;
  int local;

  for(int i = 0; i < n; i++){

    pthread_mutex_lock(&lock);

    local = global;
    local++;
    global = local;
    fprintf(stdout,"Thread Utility => Global = %d\n", global);

    pthread_mutex_unlock(&lock);

    sleep(1);
  }

  fprintf(stdout,"⚡️ Final Result from Thread Utility => Global = %d ⚡️\n", global);


  pthread_exit((int *) 0);

}