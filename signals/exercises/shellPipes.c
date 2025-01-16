/*
 * Illustrates the use of shell pipes (!!!)
 *
 * To compile: gcc -Wall shellPipes.c -o app
 * Example: ls | .app 
 */

#include <stdio.h>
#include <stdlib.h>

int main ()
{
  char buf[1024];

  while (gets(buf)) {
    printf ("PIPE EXAMPLE: ");
    puts(buf);
  }

  return (0);
}