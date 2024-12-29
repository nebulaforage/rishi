#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

// Structure to represent a memory block
typedef struct {
    int size;
    int allocated;
} MemoryBlock;

// Structure to represent a process
typedef struct {
    int size;
    int allocatedBlock;
} Process;

void firstFit(MemoryBlock blocks[], int blockCount, Process processes[], int processCount) {
    for (int i = 0; i < processCount; i++) {
        processes[i].allocatedBlock = -1; // Unallocated by default
        for (int j = 0; j < blockCount; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                processes[i].allocatedBlock = j;
                blocks[j].allocated = 1;
                break;
            }
        }
    }
}

void bestFit(MemoryBlock blocks[], int blockCount, Process processes[], int processCount) {
    for (int i = 0; i < processCount; i++) {
        processes[i].allocatedBlock = -1; // Unallocated by default
        int bestIdx = -1;
        for (int j = 0; j < blockCount; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                if (bestIdx == -1 || blocks[j].size < blocks[bestIdx].size) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            processes[i].allocatedBlock = bestIdx;
            blocks[bestIdx].allocated = 1;
        }
    }
}

void worstFit(MemoryBlock blocks[], int blockCount, Process processes[], int processCount) {
    for (int i = 0; i < processCount; i++) {
        processes[i].allocatedBlock = -1; // Unallocated by default
        int worstIdx = -1;
        for (int j = 0; j < blockCount; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                if (worstIdx == -1 || blocks[j].size > blocks[worstIdx].size) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            processes[i].allocatedBlock = worstIdx;
            blocks[worstIdx].allocated = 1;
        }
    }
}

void printAllocation(Process processes[], int processCount, MemoryBlock blocks[]) {
    printf("\nProcess Allocation:\n");
    printf("Process\tSize\tAllocated Block\n");
    for (int i = 0; i < processCount; i++) {
        printf("%d\t%d\t", i + 1, processes[i].size);
        if (processes[i].allocatedBlock != -1) {
            printf("%d\n", processes[i].allocatedBlock + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
    printf("\n");
}

int main() {
    int blockCount, processCount;

    // Input memory blocks
    printf("Enter the number of memory blocks: ");
    scanf("%d", &blockCount);
    MemoryBlock blocks[MAX_BLOCKS];
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < blockCount; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i].size);
        blocks[i].allocated = 0; // Initially, all blocks are unallocated
    }

    // Input processes
    printf("Enter the number of processes: ");
    scanf("%d", &processCount);
    Process processes[MAX_PROCESSES];
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < processCount; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].size);
    }

    int choice;
    do {
        printf("\nMemory Allocation Strategies:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Reset block allocations
        for (int i = 0; i < blockCount; i++) {
            blocks[i].allocated = 0;
        }

        switch (choice) {
            case 1:
                firstFit(blocks, blockCount, processes, processCount);
                printAllocation(processes, processCount, blocks);
                break;
            case 2:
                bestFit(blocks, blockCount, processes, processCount);
                printAllocation(processes, processCount, blocks);
                break;
            case 3:
                worstFit(blocks, blockCount, processes, processCount);
                printAllocation(processes, processCount, blocks);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

