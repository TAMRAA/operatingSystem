/*
 * mutex.c
 *
 * Illustrates the use of mutex
 * for mutual exclusion
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *threadUtility(void *arg) {

  // We can skip adding pthread_join() like that
  pthread_detach(pthread_self());

  while (counter <= 10) {
    pthread_mutex_lock(&mutex);
    counter++;
    printf("Counter = %d\n", counter);
    pthread_mutex_unlock(&mutex);
    sleep(2);
  }

  pthread_exit((int *) 0);
}


int main() {

  pthread_t thread1, thread2;

  setbuf(stdout, NULL); // Disable buffering for stdout

  pthread_create(&thread1, NULL, threadUtility, NULL);
  pthread_create(&thread2, NULL, threadUtility, NULL);

  pthread_exit(NULL);
}
