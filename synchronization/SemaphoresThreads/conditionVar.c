#include <stdio.h>
#include <pthread.h>

#define bufferSize 16
#define OVER (-1)    // Special value to indicate the end of production

// Shared buffer structure (circular buffer)
typedef struct {

    int buffer[bufferSize];       // The buffer array
    int writepos, readpos, count; // Positions for writing, reading, and item count
    pthread_mutex_t lock;         // Mutex for synchronization
    pthread_cond_t notempty;      // Condition: buffer is not empty
    pthread_cond_t notfull;       // Condition: buffer is not full

} prodcons;

// Global buffer used by both producer and consumer
prodcons buffer;

// Initialize the buffer and synchronization tools
void init(prodcons *arg) {

    pthread_mutex_init(&arg->lock, NULL);
    pthread_cond_init(&arg->notempty, NULL);
    pthread_cond_init(&arg->notfull, NULL);
    arg->writepos = 0;                            // Start writing at position 0.
    arg->readpos = 0;                             // Start reading at position 0.
    arg->count = 0;                               // Start with an empty buffer.
}

// Add an item to the buffer (producer function)
void put(prodcons *arg, int data) {
    pthread_mutex_lock(&arg->lock);               // Lock the buffer.
    while (arg->count == bufferSize) {            // If the buffer is full...
        pthread_cond_wait(&arg->notfull, &arg->lock); // Wait for space
    }
    arg->buffer[arg->writepos] = data;              // Add the item to the buffer.
    arg->writepos = (arg->writepos + 1) % bufferSize; // Move to the next position (circular).
    arg->count++;                                 // Increment item count.
    pthread_cond_signal(&arg->notempty);          // Signal that the buffer is not empty.
    pthread_mutex_unlock(&arg->lock);             // Unlock the buffer.
}

// Remove an item from the buffer (consumer function).
int get(prodcons *arg) {
    pthread_mutex_lock(&arg->lock);               // Lock the buffer.
    while (arg->count == 0) {                     // If the buffer is empty...
        pthread_cond_wait(&arg->notempty, &arg->lock); // Wait for items.
    }
    int data = arg->buffer[arg->readpos];           // Retrieve the item from the buffer.
    arg->readpos = (arg->readpos + 1) % bufferSize; // Move to the next position (circular).
    arg->count--;                                 // Decrement item count.
    pthread_cond_signal(&arg->notfull);           // Signal that the buffer is not full.
    pthread_mutex_unlock(&arg->lock);             // Unlock the buffer.
    return data;
}

// Producer thread function.
void *producer(void *data) {
    for (int n = 0; n < 10000; n++) {
        printf("%d Package -->\n", n);                // Print the produced item.
        put(&buffer, n);                       // Add the item to the buffer.
    }
    put(&buffer, OVER);                        // Add the termination signal.
    return NULL;
}

// Consumer thread function
void *consumer(void *data) {
    int d;
    while (1) {

        d = get(&buffer); // Retrieve an item from the buffer
        if (d == OVER){ // Stop if the termination signal is received
            break;
        }
        printf("---> Delivered %d\n", d);                // Print the consumed item.
    }
    return NULL;
}

// Main function to create threads and start the process.
int main(void) {

    pthread_t producer_thread, consumer_thread; // Thread handles.

    init(&buffer);                              // Initialize the buffer.

    pthread_create(&producer_thread, NULL, producer, NULL); // Start the producer thread.
    pthread_create(&consumer_thread, NULL, consumer, NULL); // Start the consumer thread.

    pthread_join(producer_thread, NULL);        // Wait for the producer to finish.
    pthread_join(consumer_thread, NULL);        // Wait for the consumer to finish.

    return 0;
}
