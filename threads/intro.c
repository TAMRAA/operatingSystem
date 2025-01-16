// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>



// Main function
int main(int argc, char **argv){

    pthread_t thread1 = NULL;
    pthread_t thread2 = NULL;

    int c = pthread_equal(thread1, thread2);

    fprintf(stdout,"Return => %d => :)\n", c);

    return 0;
}

// Function Signatures
pthread_t pthread_self (void);
int pthread_create (pthread_t *tid,const pthread_attr_t *attr,void *(*startRoutine)(void *),void *arg);

/*

Arguments
---------
1) Identifier of the generated thread (tid)
2) NULL is the default attribute
3) C function executed by the thread (startRoutine)
4) Argument passed to the start routine (arg),
NULL if no argument

Returned values
---------------
1) 0 on success
2) Error code on failure

*/
