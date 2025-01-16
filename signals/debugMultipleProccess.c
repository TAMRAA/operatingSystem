/*
 * StQ 05.04.2011
 *
 * Demo: How to debug concurrent processes
 *
 *
 * 1 - insert in the father and in the child to debug a
 *     a print of the pid, a pause (to pause the process
 *     in order to wait the signal) and a specific line to
 *     start the debug
 * 2 - compile with the -g option (no optimizations)
 *     gcc -Wall -g -o <exe> <source> -lm
 * 3 - execute the pgrm in the first shell
 * 4 - execute "sudo gdb" in the second shell (used to debug the parent)
 *     In this debug shell type:
 *     - file <exe>      to load the table of symbols of the program to debug
 *     - attach <pid>    inserting the pid of the parent (that you want to debug)
 *     - break <n>       con n = numero riga in cui si vuole incomiciare il debug
 *     - signal SIGUSR1  to wake up the parent blocked on pause
 * 5 - the same for the child
 * 6 - you can debug father and child in the two separate shells
 *
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

void signalParent (int);
void signalChild (int);

int
child (
  int sec
  )
{
  fprintf(stdout,"CHILD%d: Start!\n", getpid());
  fprintf(stdout,"CHILD%d: Sleep!\n",getpid());
  sleep(sec);
  fprintf(stdout, "CHILD%d: I'm the child of %d. "
    "Don't sleep and finish!\n",getpid(),getppid());

  return 0;
}

int
father (
  )
{
  int status;
  fprintf(stdout, "PARENT: I'm the parent %d!\n", getpid());
  fprintf(stdout, "PARENT: Sleep!\n");
  sleep(1);
  fprintf(stdout, "PARENT: Don't sleep!\n");
  fprintf(stdout, "PARENT: Waited child  %d\n",wait(&status));
  fprintf(stdout, "PARENT: Finish!\n");

  return 0;
}

int
main (
  void
  )
{
  switch (fork()){
    case -1:
      fprintf (stderr, "Fork error.\n");
      return 1;
    case 0 :
      fprintf (stdout, "Child pid = %d\n", getpid());
      signal (SIGUSR1, signalChild);
      pause();
      fprintf (stdout, "Breakpoint line.\n");
      child(10);
      break;
    default:
      fprintf (stdout, "Parent pid = %d\n", getpid());
      signal(SIGUSR1, signalParent);
      pause();
      fprintf (stdout, "Breakpoint line.\n");
      father();
      break;
  }

  printf("End of the process %d\n",getpid());
  return 0;
}

void
signalChild (
  int signum
  )
{
  fprintf (stdout, "Child pid = %d\n", getpid());
}

void
signalParent (
  int signum
  )
{
  fprintf (stdout, "Parent pid = %d\n", getpid());
}