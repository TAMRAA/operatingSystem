#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *threadUtility(){

    fprintf(stdout,"Hello From Thread Utility 😃\n");
    sleep(1);
    fprintf(stdout,"Thread Utility Checked out ✅\n");
    pthread_exit((int *) 0);
}
int main (int argc, char **argv){

    pthread_t tid;
    int rc;

    fprintf(stdout,"I am main thread 🙂\n");

    rc = pthread_create(&tid, NULL, threadUtility, NULL);
    if(rc){
        fprintf(stderr,"Thread creation failed ❌\n");
        abort();
    }

    if(argc > 1){
        pthread_detach(tid);
    }

    sleep(1);
    rc = pthread_join(tid, NULL);
    if(rc){
        fprintf(stderr,"Thread failed to join 😕\n ");
        exit(1);
    }
    fprintf(stdout,"Main Thread Checked out ✅\n");

    pthread_exit((int *) 0);
}