#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define numThreads 8


char *messages[numThreads];

void *threadUtility(void *thId){
  int threadId = * (int *)thId;
  fprintf(stdout,"Thread %d says => %s\n", threadId + 1, messages[threadId]);

  free(thId);
  pthread_exit((int *) 0);

}


int main(int argc, char **argv){
  pthread_t threads[numThreads];
  int *threadId;
  int status;

  messages[0] = "English: Hello World!";
  messages[1] = "French: Bonjour, le monde!";
  messages[2] = "Spanish: Hola al mundo";
  messages[3] = "Klingon: Nuq neH!";
  messages[4] = "German: Guten Tag, Welt!";
  messages[5] = "Russian: Zdravstvytye, mir!";
  messages[6] = "Japan: Sekai e konnichiwa!";
  messages[7] = "Latin: Orbis, te saluto!";

  for(int i = 0; i < numThreads; i++){
    fprintf(stdout,"Initializing thread %d...\n", i+1);
    threadId = (int *) malloc (sizeof(int));
    if(threadId == NULL){
      fprintf(stderr,"Memory allocation failed\n");
      exit(404);
    }
    // Assign unique thread id
    *threadId = i;
    status = pthread_create(&threads[i], NULL, threadUtility, (void *) threadId);
    if(status){
      fprintf(stderr,"Threading 404\n");
      exit(404);
    }
  }

  pthread_exit((int *) 0);
}