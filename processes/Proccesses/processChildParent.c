
// Illustrates system call fork

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc,char *argv[]){


  int tC = atoi (argv[1]);  // time sleep for child and parent
  int tP =  atoi (argv[2]);
  pid_t pid;



  // Main Process
  fprintf (stdout, "Main Process => ");
  fprintf (stdout, "PID = %d; My parent PID = %d\n\n", getpid(), getppid());


  pid = fork();

  // Child Process
  if (pid == 0){
    sleep (tC);

    // Print Process Info's
    fprintf(stdout, "Child Process => PIDreturned = %d ; ", pid);
    fprintf (stdout, "PID = %d; My parent PID = %d\n\n",getpid(), getppid());
  }

  // Parent Process
  else {

    // Sleep a bit
    sleep (tP);

    // Print Process Info's
    fprintf(stdout, "Father Process => PIDreturned = %d ;", pid);
    fprintf (stdout,"PID = %d; My parent PID = %d\n\n", getpid(), getppid());
  }

  return 0;
}