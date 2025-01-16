/*
 * Illustrates the use of the system calls
 * signal, alarm, and pause 
 */ 

#include <stdio.h>		
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


// function Prototypes
void catcher1 ();
void catcher2 ();


// used to toggle between the two signal-handling functions (catcher1 and catcher2)
int i = 0;

int main (void) {
  /*
   * declaration for the kernel. It means:
   * I don't want to die (default action)
   * when I receive a SIGALRM signal, instead
   * I will execute function "catcher"
   */
  signal (SIGALRM, catcher1);

  /* The alarm wakes up the pause after 5 sec and the two catchers are inverted */
  while(1) {
    alarm(5);
    fprintf(stdout, "waiting begins\n");
    fflush (stdout);
    pause();
    fprintf(stdout, "end wait\n"); 
    fflush (stdout);
  }

  return EXIT_SUCCESS;
}


// Function Declarations

void catcher1() {

    fprintf(stdout,"catcher 1: ");
    fflush(stdout);  // Ensures the output is immediately displayed

    system("date");  // Runs the `date` command to show the current date and time

    // Sets the next signal handler based on the value of `i`
    if (i == 1) {
        signal(SIGALRM, catcher1);
    } else {
        signal(SIGALRM, catcher2);
    }

    // Toggle `i` between 0 and 1
    i = 1 - i;
    return;
}

void catcher2() {
    fprintf(stdout, "catcher 2: ");
    fflush(stdout);

    system("date");

    if (i == 1) {
        signal(SIGALRM, catcher1);
    } else {
        signal(SIGALRM, catcher2);
    }

    i = 1 - i;
    return;
}