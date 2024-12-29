#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Declare a mutex
pthread_mutex_t lock;

// Shared resource
int counter = 0;

// Function that will be executed by each thread
void* increment_counter(void* arg) {
    pthread_mutex_lock(&lock);  // Lock the mutex
    printf("Thread %ld: Incrementing counter...\n", pthread_self());
    counter++;  // Increment the counter
    printf("Thread %ld: Counter = %d\n", pthread_self(), counter);
    pthread_mutex_unlock(&lock);  // Unlock the mutex
    return NULL;
}

int main() {
    pthread_t threads[5];  // Create an array of thread IDs

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed!\n");
        return 1;
    }

    // Create 5 threads
    for (int i = 0; i < 5; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            printf("Thread creation failed!\n");
            return 1;
        }
    }

    // Join all threads (ensure they complete before the program ends)
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    // Final value of the counter
    printf("Final Counter Value: %d\n", counter);
    return 0;
}

