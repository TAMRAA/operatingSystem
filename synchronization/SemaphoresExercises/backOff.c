#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define EBUSY 2 // Mutex busy error code
#define ITERATIONS 10 // Number of iterations for each thread to run

/*
 * Initialize a static array of 3 mutexes
 */
pthread_mutex_t mutex[3] = {
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER
};

/*
 * This is a thread start routine that locks all mutexes in
 * order, to ensure a conflict with lock_reverse, which does the
 * opposite.
 */
void *lockForward(void *arg) {
    int i, iterate, backoffs;
    int status;

    for (iterate = 0; iterate < ITERATIONS; iterate++) {
        backoffs = 0;
        status = pthread_mutex_lock (&mutex[0]);

        for (i = 1; i < 3; i++) {
            status = pthread_mutex_trylock (&mutex[i]);

            if (status == EBUSY) {
                // Backoff mechanism: count the backoffs and release the acquired mutexes
                backoffs++;
                printf("forward locker backing off at %d\n", i);

                for (; i >= 0; i--) {
                    pthread_mutex_unlock (&mutex[i]);
                }
            } else {
                printf(" forward locker got %d\n", i);
            }
        }
        sleep (1); // Optional yield mechanism
    }

    // Report that we got 'em, and unlock to try again
    printf ("lock forward got all locks, %d backoffs\n", backoffs);

    pthread_mutex_unlock (&mutex[2]);
    pthread_mutex_unlock (&mutex[1]);
    pthread_mutex_unlock (&mutex[0]);

    sleep (1);

    return NULL;
}

/*
 * This is a thread start routine that locks all mutexes in
 * reverse order, to ensure a conflict with lockForward, which
 * does the opposite.
 */
void *lockBackward (void *arg) {
    int i, iterate, backoffs;
    int status;

    for (iterate = 0; iterate < ITERATIONS; iterate++) {
        backoffs = 0;
        status = pthread_mutex_lock (&mutex[2]);
        for (i = 1; i >= 0; i--) {
            status = pthread_mutex_trylock (&mutex[i]);
            if (status == EBUSY) {
                // Backoff mechanism: count the backoffs and release all acquired mutexes
                backoffs++;
                printf("backward locker backing off at %d\n", i);

                for (; i < 3; i++) {
                    pthread_mutex_unlock (&mutex[i]);
                }
            } else {
                printf(" backward locker got %d\n", i);
            }
        }
        sleep (1); // Optional yield mechanism
    }

    // Report that we got 'em, and unlock to try again
    printf ("lock forward got all locks, %d backoffs\n", backoffs);

    pthread_mutex_unlock (&mutex[2]);
    pthread_mutex_unlock (&mutex[1]);
    pthread_mutex_unlock (&mutex[0]);
    sleep (1);

    return NULL;
}

int main (int argc, char *argv[]) {
    pthread_t forward, backward;
    int status;
    int yield_flag;

    // If the second argument is absent, or zero, the two threads run "at speed."
    if (argc > 2) {
        yield_flag = atoi (argv[2]);
    }

    // Create forward locker thread
    status = pthread_create (&forward, NULL, lockForward, NULL);
    if (status != 0) {
        fprintf (stderr, "Create forward");
    }

    // Create backward locker thread
    status = pthread_create (&backward, NULL, lockBackward, NULL);
    if (status != 0) {
        fprintf (stderr, "Create backward");
    }

    pthread_exit (NULL);
}
