#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>

/*
  This code demonstrates a multi-threaded application written in C that reads characters from a file,
  converts them to uppercase, and then prints them to the standard output

  ### Summary

  1. The code opens a file and reads characters one by one

  2. Each character is read by the `GET` thread, converted to uppercase by the `UPDATE` thread,
  and printed by the `PRINT` thread

  3. The main loop continues until the end of the file is reached

  4. The program ensures proper synchronization by using `pthread_join` to wait for each thread
  to finish before proceeding :)

*/


/* Global Variables */
char next, this, last;
FILE *fp;


/* Threads Utilities */

void abortMission(int status){
  fprintf(stderr,"Threads 404 with status = %d\n", status);
  exit(404);
}


static void *GET(void *arg) {
  char *c = (char *) arg;
  *c = fgetc(fp);  // Read character from file
  return NULL;
}

static void *UPDATE(void *arg) {
  char *c = (char *) arg;
  *c = toupper(*c);
  return NULL;
}

static void *PRINT(void *arg) {
  char *c = (char *) arg;
  putchar(*c);  // Print character
  return NULL;
}


// Main Function
int main(int argc, char **argv) {

  /* Unique thread for each operation */
  pthread_t getThread, updateThread, printThread;
  void *returnValue;
  int status;

  if (argc < 2 ) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(1);
  }

  if ((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr,"Input file doesn't exist!");
    exit(1);
  }

  this = ' ';
  last = ' ';
  next = ' ';

  while (next != EOF) {

    /* Break the loop in case if EOF */
    if (next == EOF){
      break;
    }

    /* CREATE GET THREAD */

    status = pthread_create(&getThread, NULL, GET, &next);
    if (status){
      abortMission(status);
    }
    status = pthread_join(getThread, &returnValue);
    if (status){
      abortMission(status);
    }


    /* CREATE UPDATE THREAD */
    status = pthread_create(&updateThread, NULL, UPDATE, &this);
    if (status) {
      abortMission(status);

    }
    /* CREATE PRINT THREAD */
    status = pthread_create(&printThread, NULL, PRINT, &last);
    if (status) {
      abortMission(status);
    }

    // WAIT FOR THEM TO JOIN BACK=> Comeback
    status = pthread_join(updateThread, &returnValue);
    if (status) {
      abortMission(status);

    }
    status = pthread_join(printThread, &returnValue);
    if (status) {
      abortMission(status);

    }

    // UPDATE INDICES
    last = this;
    this = next;
  }


  // PROCESS THE LAST 2 CHARACTERS

  /* CREATE UPDATE THREAD */
  status = pthread_create(&updateThread, NULL, UPDATE, &this);
  if (status) {
    abortMission(status);
  }
  status = pthread_join(updateThread, &returnValue);
  if (status) {
    abortMission(status);
  }

  /* CREATE PRINT THREAD */


  status = pthread_create(&printThread, NULL, PRINT, &this);
  if (status) {
    abortMission(status);
  }
  status = pthread_join(printThread, &returnValue);
  if (status) {
    abortMission(status);
  }

  status = pthread_create(&printThread, NULL, PRINT, &last);
  if (status) {
    abortMission(status);
  }
  status = pthread_join(printThread, &returnValue);
  if (status) {
    abortMission(status);
  }

  fclose(fp);
  return 0;
}