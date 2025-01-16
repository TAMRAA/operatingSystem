#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 




void signalHandler(int signo){
  if(signo == SIGUSR1){
    fprintf(stdout,"Signal USR1 Received :)\n");
  }else if(signo == SIGUSR2){
    fprintf(stdout,"Signal USR2 Received :)\n");
  }else{
    fprintf(stdout,"Signal %d Received :)\n", signo);
  }
  return;
}

int main(void){
  if(signal(SIGUSR1, signalHandler) == SIG_ERR){
    fprintf(stderr,"Signal SIGUSR1 is not sent :(\n");
  }else if(signal(SIGUSR2, signalHandler) == SIG_ERR){
    fprintf(stderr,"Signal SIGUSR2 is not sent :(\n");
  }else{
    signalHandler(SIGUSR1);
    signalHandler(SIGUSR2);

    while (1)
    {
      fprintf(stdout,"Before Sleeping...\n");
      sleep(2);
      fprintf(stdout,"After Sleeping :)\n");
    }
    
  }

  return EXIT_SUCCESS;

}