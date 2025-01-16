#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define threadNum 8

sem_t semEmpty, semFull;
pthread_mutex_t mutexBuffer;

int buffer[10];
int count = 0;


static void *producer(void *args){
  while (1)
  {
    // Produce
    int x = rand() % 100;  // 0-99

    sem_wait(&semEmpty);
    pthread_mutex_lock(&mutexBuffer);
    // We have space in that buffer => we can add

    // Add to buffer
    buffer[count] = x;
    count++;

    pthread_mutex_unlock(&mutexBuffer);
    sem_post(&semFull);
    sleep(1);
  }

  pthread_exit((int *) 0);
}

static void *consumer(void *args){
  while (1)
  {
    int y = -1;

    //
    sem_wait(&semFull);
    pthread_mutex_lock(&mutexBuffer);

    // take something from the buffer only when

    // Remove from buffer
    y = buffer[count - 1];
    count--;


    pthread_mutex_unlock(&mutexBuffer);
    sem_post(&semEmpty);

    // Consume -1 cpu cycle for doing nothing!
    fprintf(stdout,"Got %d\n", y);
    sleep(1);
  }


  pthread_exit((int *) 0);
}


int main(void){

  srand(time(NULL));
  pthread_t threads[threadNum];

  pthread_mutex_init(&mutexBuffer, NULL);
  sem_init(&semEmpty, 0, 10); // Number of slots available at the beginning
  sem_init(&semFull, 0, 0);   // Number of filled up elements

  for(int i = 0; i < threadNum; i++){
    // Control num of producers
    if(i > 0){
      // Half of threads gonna be producer
      if(pthread_create(&threads[i], NULL, &producer, NULL) != 0){
        perror("Threading 404\n");
      }
    }else{
      // Half of threads gonna be consumer
      if(pthread_create(&threads[i], NULL, &consumer, NULL) != 0){
        perror("Threading 404\n");
      }
    }
  }

  for(int i = 0 ; i < threadNum ; i++){
    if(pthread_join(threads[i], NULL) != 0){
      perror("Joining threads 404\n");
    }
  }
  sem_destroy(&semEmpty);
  sem_destroy(&semFull);
  pthread_mutex_destroy(&mutexBuffer);
  return 0;
}