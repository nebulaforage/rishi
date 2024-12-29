#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define PRODUCER_COUNT 1
#define CONSUMER_COUNT 1

// Buffer and semaphores
int buffer[BUFFER_SIZE];
int in = 0; // Index for the producer to add items
int out = 0; // Index for the consumer to remove items

sem_t empty; // Semaphore to count empty slots
sem_t full;  // Semaphore to count full slots
sem_t mutex; // Semaphore to ensure mutual exclusion

// Producer thread function
void *producer(void *param) {
    int item;
    
    while (1) {
        // Produce an item
        item = rand() % 100; // Generate random number as item
        sleep(1);
        
        // Wait for an empty slot in the buffer
        sem_wait(&empty);
        
        // Wait for mutual exclusion
        sem_wait(&mutex);
        
        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer produced item %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        
        // Release mutual exclusion
        sem_post(&mutex);
        
        // Signal that there's a full slot
        sem_post(&full);
    }
}

// Consumer thread function
void *consumer(void *param) {
    int item;
    
    while (1) {
        // Wait for a full slot in the buffer
        sem_wait(&full);
        
        // Wait for mutual exclusion
        sem_wait(&mutex);
        
        // Remove an item from the buffer
        item = buffer[out];
        printf("Consumer consumed item %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        
        // Release mutual exclusion
        sem_post(&mutex);
        
        // Signal that there's an empty slot
        sem_post(&empty);
        
        // Simulate consumption time
        sleep(1);
    }
}

int main() {
    pthread_t producers[PRODUCER_COUNT];
    pthread_t consumers[CONSUMER_COUNT];
    
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all buffer slots are empty
    sem_init(&full, 0, 0); // Initially, there are no full slots
    sem_init(&mutex, 0, 1); // Mutex is initially available
    
    // Create producer and consumer threads
    for (int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }
    
    for (int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }
    
    // Wait for threads to finish (they won't in this infinite loop)
    for (int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_join(producers[i], NULL);
    }
    
    for (int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_join(consumers[i], NULL);
    }
    
    // Cleanup semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    
    return 0;
}

