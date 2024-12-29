#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    // array to keep track of whether a block is allocated
    int allocation[n];
    
    // Initialize all allocations as -1 (no block allocated)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Iterate through each process
    for (int i = 0; i < n; i++) {
        // Find the first block that can accommodate the process
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate the block to the process
                allocation[i] = j;

                // Reduce the size of the block
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    // Print the result
    printf("Process No.\tProcess Size\tBlock No.\tBlock Size\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\t\t%d\n", allocation[i] + 1, blockSize[allocation[i]]);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    // Number of blocks
    int m = 5;
    // Number of processes
    int n = 4;
    
    // Size of blocks
    int blockSize[] = {100, 500, 200, 300, 600};
    
    // Size of processes
    int processSize[] = {212, 417, 112, 426};

    // Call firstFit function to allocate memory
    firstFit(blockSize, m, processSize, n);

    return 0;
}

