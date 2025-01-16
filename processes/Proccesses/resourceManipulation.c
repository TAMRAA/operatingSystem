#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Fork execution order

int main(){
  char ch = 'X';
  char str[10];

  printf("Welcome to my app :)\n");
  if(fork()){
    ch = 'P';
    strcpy(str,"Parent");
    sleep(2);
  }else{
    ch = 'C';
    strcpy(str,"Child");
  }


  printf("I am process %s with character %c\npid = %d \nppid = %d \n", str, ch, getpid(), getppid());
  return 0;
}
