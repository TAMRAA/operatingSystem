/*
 *  I can write on the two directions of the pipe (half-duplex)?
 *  Yes, but alternatively ...
 *  If I write:
 *  - F on the command line, the parent writes some F and the child reads them
 *  - C on the command line, the child writes some C and the parent reads them
 *  - FC on the command line, they alternate
 *  Some sleeps are placed to avoid that R/W are done by the same process in sequence
 *  Removing the while(1) cycle, this is done only on time, and the parent does 
 *  the wait for the exit of the child.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main (
  int argc,
  char ** argv
  )
{
  int fd[2];
  char c;

  // no buffering
  setbuf (stdout, 0);

  // Create pipe
  pipe (fd);

  if (fork()!=0) {
    while (1) {
      if (strcmp (argv[1], "P")==0 || strcmp (argv[1], "PC")==0) {
        c = 'P';
        fprintf (stdout, "Parent Write %c\n", c);
        write (fd[1], &c, 1);
      }
      sleep (2);
      if (strcmp (argv[1], "C")==0 || strcmp (argv[1], "PC")==0) {
        read (fd[0], &c, 1);
        fprintf (stdout, "Parent Read %c\n", c);
      }
      sleep (2);
    }
    wait ((int *) 0);
  } else {
    while (1) {
      if (strcmp (argv[1], "P")==0 || strcmp (argv[1], "PC")==0) {
        read (fd[0], &c, 1);
        fprintf (stdout, "Child Read %c\n", c);
      }
      sleep (2);
      if (strcmp (argv[1], "C")==0 || strcmp (argv[1], "PC")==0) {
        c = 'C';
        fprintf (stdout, "Child Write %c\n", c);
        write (fd[1], &c, 1);
      }
      sleep (2);
    }
    exit (0);
  }

   return (0);
}