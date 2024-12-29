#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function that each thread will execute
void *print_message(void *thread_id) {
    long tid = (long)thread_id;
    printf("Hello from thread %ld\n", tid);
    pthread_exit(NULL);
}

int main() {
    int num_threads = 5; // Number of threads
    pthread_t threads[num_threads];
    int rc;
    long t;

    // Creating multiple threads
    for (t = 0; t < num_threads; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_message, (void *)t);
        if (rc) {
            printf("Error: Unable to create thread %d\n", rc);
            exit(-1);
        }
    }

    // Waiting for all threads to complete
    for (t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("All threads completed.\n");
    return 0;
}

