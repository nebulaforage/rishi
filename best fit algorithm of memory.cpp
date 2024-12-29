#include <stdio.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

// Function to perform Best Fit allocation
void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n]; // Array to store allocated blocks

    // Initially, no block is assigned
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Traverse through all processes
    for (int i = 0; i < n; i++) {
        // Find the best block for the process
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j]) {
                    bestIdx = j;
                }
            }
        }

        // If a block is found, allocate it to the process
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i]; // Reduce the block size
        }
    }

    // Print the allocation results
    printf("\nProcess No.\tProcess Size\tBlock No.\tBlock Size Left\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, processSize[i], allocation[i] + 1, blockSize[allocation[i]]);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, processSize[i]);
        }
    }
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int m, n;

    // Input number of memory blocks
    printf("Enter the number of blocks: ");
    scanf("%d", &m);

    // Input size of each block
    printf("Enter the sizes of the blocks: \n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input size of each process
    printf("Enter the sizes of the processes: \n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // Perform Best Fit Allocation
    bestFit(blockSize, m, processSize, n);

    return 0;
}

