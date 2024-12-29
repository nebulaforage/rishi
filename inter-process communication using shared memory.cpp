#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Define size of the shared memory region

// Structure to hold data for shared memory
struct shared_data {
    char message[SHM_SIZE];
};

int main() {
    // Create a unique key for shared memory
    key_t key = ftok("shmfile", 65);  // Use some file to generate a key
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);  // Create shared memory segment
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach the shared memory to the process's address space
    struct shared_data *shm_ptr = (struct shared_data *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Write data into the shared memory
    printf("Writing data to shared memory...\n");
    snprintf(shm_ptr->message, SHM_SIZE, "Hello from process 1!");

    // Wait for another process to read the data
    printf("Press enter to read the data...\n");
    getchar();  // Wait for user to press enter

    // Read the message from shared memory
    printf("Reading from shared memory: %s\n", shm_ptr->message);

    // Detach from shared memory
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    // Optionally, destroy the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl failed");
        exit(1);
    }

    return 0;
}

