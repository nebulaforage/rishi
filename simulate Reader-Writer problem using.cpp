#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;           // Semaphore for mutual exclusion (reader count)
sem_t write_mutex;     // Semaphore for writing (to give exclusive access to writers)
int read_count = 0;    // Count of active readers

// Reader thread function
void* reader(void* arg) {
    sem_wait(&mutex);  // Wait on mutex to safely update read_count
    read_count++;
    if (read_count == 1) {
        sem_wait(&write_mutex);  // First reader locks the write mutex
    }
    sem_post(&mutex);  // Release mutex after updating read_count

    // Reading critical section
    printf("Reader %ld is reading...\n", (long)arg);
    sleep(1);  // Simulate reading

    sem_wait(&mutex);  // Wait on mutex to safely update read_count
    read_count--;
    if (read_count == 0) {
        sem_post(&write_mutex);  // Last reader releases the write mutex
    }
    sem_post(&mutex);  // Release mutex after updating read_count

    return NULL;
}

// Writer thread function
void* writer(void* arg) {
    sem_wait(&write_mutex);  // Wait for exclusive access to the shared resource

    // Writing critical section
    printf("Writer %ld is writing...\n", (long)arg);
    sleep(2);  // Simulate writing

    sem_post(&write_mutex);  // Release write mutex after writing

    return NULL;
}

int main() {
    pthread_t readers[5], writers[3];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);          // Initialize mutex for reader count
    sem_init(&write_mutex, 0, 1);    // Initialize write mutex for exclusive writing

    // Create reader threads
    for (long i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, (void*)i);
    }

    // Create writer threads
    for (long i = 0; i < 3; i++) {
        pthread_create(&writers[i], NULL, writer, (void*)i);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&write_mutex);

    return 0;
}

