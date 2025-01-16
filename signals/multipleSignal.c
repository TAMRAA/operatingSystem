#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <signal.h>


// Function Prototypes
static void sigUsr1 (int);
static void sigUsr2 (int);


// Function Declarations
static void sigUsr1 (int signo) {
  
  if (signo == SIGUSR1){
    fprintf(stdout,"Received SIGUSR1\n");
  }

  else{
    fprintf(stdout,"Received wrong SIGNAL\n");
  }

  fprintf (stdout, "sigUsr1 sleeping ...\n");
  sleep(5);
  fprintf (stdout, "... sigUsr1 woke up :)\n");

  return;
}

static void sigUsr2 (int signo) {

  if (signo == SIGUSR2){
    fprintf(stdout, "Received SIGUSR2\n");
  }

  else{
    fprintf(stdout, "Received wrong SIGNAL\n");
  } 
  fprintf (stdout, "sigUsr2 sleeping ...\n");
  sleep (5);
  fprintf (stdout, "... sigUsr2 woke up :)\n");

  return;
}

int main (void){

  if (signal(SIGUSR1, sigUsr1) == SIG_ERR) {
    fprintf (stderr, "Signal Handler Error\n");
    return EXIT_FAILURE;
  }

  if (signal(SIGUSR2, sigUsr2) == SIG_ERR) {
    fprintf (stderr, "Signal Handler Error\n");
    return EXIT_FAILURE;
  }

  sigUsr1(SIGUSR1);

  sigUsr2(SIGUSR2);

  while (1) {
    fprintf (stdout, "Before pause\n");
    sleep(5);
    fprintf (stdout, "After pause.\n");
  }

  return EXIT_SUCCESS;
}