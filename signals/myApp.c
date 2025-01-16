#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// functions prototypes
static void signalUser1(int signo);
static void signalUser2(int signo);

int main(void){
    
    signal(SIGUSR1, signalUser1);
    signal(SIGUSR2, signalUser2);
    
    while (1)
    {
        static int i = 0;

        if(i == 0){
            fprintf(stdout,"Signal is sleeping for 5 seconds ...zzz\n");
            sleep(5);
            fprintf(stdout,"Rise and Shine Mr Signal :)\n");
        }else{
            fprintf(stdout,"Signal is sleeping again for 5 seconds ...zzz\n");
            sleep(5);
            fprintf(stdout,"Rise and Shine Mr Signal :)\n");
    
        }  
        i++;
    }
    
    return EXIT_SUCCESS;
}

// functions declarations
static void signalUser1(int signo){

    if(signo == SIGUSR1){
        fprintf(stdout,"Signal user1 activatedddd!\n");
    }else if(signo == SIGUSR2){
        fprintf(stdout,"Signal user2 cannot be activated, use the proper function call\n");
    }else{
        fprintf(stderr,"Available choices (SIGUSR1 or SIGUSR2)\n");
    }
}

static void signalUser2(int signo){
     if(signo == SIGUSR2){
        fprintf(stdout,"Signal user2 activatedddd!\n");
    }else if(signo == SIGUSR1){
        fprintf(stdout,"Signal user1 cannot be activated, use the proper function call\n");
    }else{
        fprintf(stderr,"Available choices (SIGUSR1 or SIGUSR2)\n");
    }
}
