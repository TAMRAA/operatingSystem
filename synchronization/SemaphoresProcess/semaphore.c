#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Data Structures
typedef int *semaphore;
semaphore sem; // Global Variable
int counter = 0;

// Creating a semaphore
semaphore createSemaphore(){
  int *sem;
  // Allocate 2 blocks
  sem = (int *) malloc (2 * sizeof(int));
  pipe(sem);
  return sem;
}


void WAIT(semaphore s){

  int junk;

  if(read(s[0], &junk, 1) <= 0){
    fprintf(stderr,"WAIT Error");
    exit (0);
  }
}


void SIGNAL(semaphore s){

  if(write(s[1], "x", 1) <= 0){
    fprintf(stderr,"SIGNAL Error");
    exit (0);
  }
}

void processUtil(int processId){

  for(int i = 0; i < 3; i++){
    sleep(1);
    WAIT(sem);

    // Init Critical Section
    fprintf(stdout,"Process %d entering CS...\n", processId);
    counter ++;
    sleep(1);
    fprintf(stdout,"Proccess %d finished from CS :)\n", processId);

    // Exit Critical Section
    SIGNAL(sem);
  }
}

int main(int argc, char **argv){

  int numProcess, numProcessCS;

  numProcess = atoi(argv[1]);
  numProcessCS = atoi(argv[2]);
  sem = createSemaphore();

  for(int i = 0; i < numProcessCS; i++){
    SIGNAL(sem);
    fprintf(stdout,"Semaphores %d for CS initialized :)\n", i + 1);
  }

  for(int i = 0 ; i < numProcess; i++){
    if(fork() == 0){
      fprintf(stdout,"Process %d is created :)\n", i+1);
      processUtil(i+1);
      fprintf(stdout,"Counter = %d", counter);
      exit(0);
    }
  }

  for(int i = 0; i < numProcess ; i++){
    wait(NULL);
  }

  free(sem);

  return EXIT_SUCCESS;
}