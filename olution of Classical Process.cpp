#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ITEMS 5

sem_t empty, full;    // Semaphores for empty and full slots
pthread_mutex_t mutex; // Mutex for critical section

int buffer[MAX_ITEMS]; // Shared buffer
int in = 0;            // Index for the producer
int out = 0;           // Index for the consumer

void *producer(void *param) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item (random number)
        
        sem_wait(&empty);     // Decrement empty slots
        pthread_mutex_lock(&mutex); // Enter critical section
        
        buffer[in] = item; // Place item in the buffer
        printf("Producer produced: %d\n", item);
        in = (in + 1) % MAX_ITEMS; // Update the in index
        
        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Increment full slots
        
        sleep(1); // Sleep to simulate time taken to produce
    }
}

void *consumer(void *param) {
    int item;
    while (1) {
        sem_wait(&full);      // Decrement full slots
        pthread_mutex_lock(&mutex); // Enter critical section
        
        item = buffer[out];  // Consume an item from the buffer
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % MAX_ITEMS; // Update the out index
        
        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Increment empty slots
        
        sleep(1); // Sleep to simulate time taken to consume
    }
}

int main() {
    pthread_t prod, cons;
    
    // Initialize the semaphores
    sem_init(&empty, 0, MAX_ITEMS);  // Initially, all slots are empty
    sem_init(&full, 0, 0);            // Initially, no items are produced
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    // Create the producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for the threads to finish (in this case, they'll run forever)
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Clean up semaphores and mutexes
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

