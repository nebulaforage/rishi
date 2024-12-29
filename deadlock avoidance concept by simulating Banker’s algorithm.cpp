#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];  // Available instances of resources
int maximum[MAX_PROCESSES][MAX_RESOURCES];  // Maximum demand of each process
int allocation[MAX_PROCESSES][MAX_RESOURCES];  // Resources allocated to each process
int need[MAX_PROCESSES][MAX_RESOURCES];  // Remaining resource needs of each process

// Function to calculate the need matrix
void calculateNeed() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};  // Finish status of each process
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    // Initialize work with available resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    // Try to find a safe sequence
    while (count < MAX_PROCESSES) {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                // Check if the process can be completed
                bool canFinish = true;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }

                // If the process can be completed, update work and finish
                if (canFinish) {
                    for (int j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                    break;
                }
            }
        }

        // If no process can be completed, system is not in a safe state
        if (!found) {
            return false;
        }
    }

    printf("Safe Sequence: ");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

// Function to request resources from the system
bool requestResources(int processID, int request[]) {
    // Check if request is less than the need of the process
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[processID][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Check if request is less than or equal to available resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > available[i]) {
            printf("Resources not available.\n");
            return false;
        }
    }

    // Pretend to allocate the resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[processID][i] += request[i];
        need[processID][i] -= request[i];
    }

    // Check if the system is in a safe state
    if (isSafe()) {
        printf("Resources allocated successfully.\n");
        return true;
    } else {
        // Rollback the allocation if not safe
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[processID][i] -= request[i];
            need[processID][i] += request[i];
        }
        printf("Request cannot be granted due to safety concerns.\n");
        return false;
    }
}

int main() {
    // Initialize available resources
    printf("Enter available resources:\n");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &available[i]);
    }

    // Initialize maximum resources
    printf("Enter maximum resources for each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("Maximum resources for Process P%d, Resource R%d: ", i, j);
            scanf("%d", &maximum[i][j]);
        }
    }

    // Initialize allocated resources
    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("Allocated resources for Process P%d, Resource R%d: ", i, j);
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate the need matrix
    calculateNeed();

    // Check if the system is in a safe state initially
    if (!isSafe()) {
        printf("System is not in a safe state.\n");
        return 0;
    }

    // Handle resource requests
    int processID, request[MAX_RESOURCES];
    printf("Enter the process ID for requesting resources: ");
    scanf("%d", &processID);
    printf("Enter the resource request for Process P%d:\n", processID);
    for (int i = 0; i < MAX_RESOURCES; i++) {
        printf("Request for Resource R%d: ", i);
        scanf("%d", &request[i]);
    }

    // Try to request resources
    requestResources(processID, request);

    return 0;
}

