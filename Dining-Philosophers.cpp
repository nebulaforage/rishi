#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Number of philosophers

// Semaphores and mutex
sem_t chopsticks[N];
pthread_mutex_t mutex;

// Function for philosopher actions
void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 3 + 1);

        // Pick up chopsticks
        pthread_mutex_lock(&mutex);
        sem_wait(&chopsticks[id]);
        sem_wait(&chopsticks[(id + 1) % N]);
        pthread_mutex_unlock(&mutex);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(rand() % 2 + 1);

        // Put down chopsticks
        sem_post(&chopsticks[id]);
        sem_post(&chopsticks[(id + 1) % N]);
        printf("Philosopher %d finished eating and is thinking again.\n", id);
    }
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize semaphores and mutex
    for (int i = 0; i < N; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }
    pthread_mutex_init(&mutex, NULL);

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for threads to finish (though they run infinitely)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores and mutex
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopsticks[i]);
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}

