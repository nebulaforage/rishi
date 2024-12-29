#include <stdio.h>

void worstFit(int blockSize[], int m, int processSize[], int n) {
    // Array to track whether a block is allocated or not
    int allocation[n];

    // Initially, all blocks are unallocated
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Allocate memory blocks to processes
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;

        // Find the largest block that is large enough to accommodate the process
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        // If we found a suitable block, allocate the block and mark it
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    // Output the results
    printf("\nProcess No.\tProcess Size\tBlock No.\tBlock Size\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, processSize[i], allocation[i] + 1, blockSize[allocation[i]]);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, processSize[i]);
        }
    }
}

int main() {
    int m, n;

    // Get the number of memory blocks and processes
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int blockSize[m], processSize[n];

    // Get the size of each memory block
    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Get the size of each process
    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // Call the worst fit algorithm
    worstFit(blockSize, m, processSize, n);

    return 0;
}

