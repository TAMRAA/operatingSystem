/*
 * Run as:
 * pgrm 1 10 1 & -> child becames zombie
 * pgrm 1 10 2 & -> parent manages SIG_CHLD, while child becames zombie
 * pgrm 1 10 3 & -> parent raises SIG_IGN (synch), while child DOES NOT became zombie
 * pgrm 1 10 4 & -> parent executes wait (synch), while child DOES NOT became zombie
 * and check status with -> ps -l
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static void
sigChld (
  int signo
) {
  if (signo == SIGCHLD)
    printf("Received SIGCHLD\n");
  else
    printf("Received wrong SIGNAL\n");

  sleep (5);

  return;
}

int
main (
  int argc,
  char *argv[]
  )
{
  int tC, tF, flag;
  pid_t pid;

  tC = atoi (argv[1]);
  tF = atoi (argv[2]);
  flag = atoi (argv[3]);

  pid = fork();
  if (pid == 0){
    // Child
    fprintf(stdout, "Chlld sleeps (%d secs) and returns.\n", tC);
    sleep (tC);
    exit (1);
  } else {
    // Parent
    switch (flag) {
      case 1:
        fprintf(stdout, "Parent sleeps (%d secs) and returns (child==zombie).\n", tF);
        sleep (tF);
        break;
      case 2:
        if (signal(SIGCHLD, sigChld) == SIG_ERR) {
          fprintf (stderr, "Signal Handler Error.\n");
          return (1);
        }
        fprintf(stdout, "Parent sleeps (%d secs) and deals with SIG_CHLD (child=zombie).\n", tF);
        sleep (tF);
        break;
      case 3:
        if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
          fprintf (stderr, "Signal Handler Error.\n");
          return (1);
        }
        fprintf(stdout, "Parent sleeps (%d secs) and IGNORE signal (child=NOzombie).\n", tF);
        sleep (tF);
        break;
      case 4:
        fprintf(stdout, "Parent waits and sleeps (%d secs) and waits (child=NOzombie).\n", tF);
        wait ((int *) 0);
        sleep (tF);
        break;
      default:
        fprintf(stdout, "Parent Error.\n");
      }
  }

  return 0;
}