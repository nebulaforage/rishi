#include <stdio.h>
#include <stdlib.h>

// Define maximum file size and number of blocks
#define MAX_FILE_SIZE 5
#define NUM_BLOCKS 10

// Simulate the file structure
typedef struct {
    int indexBlock[NUM_BLOCKS];  // Index block to store pointers to data blocks
    int dataBlocks[NUM_BLOCKS];  // Data blocks to store actual file data
} FileSystem;

// Function to initialize the file system
void initializeFileSystem(FileSystem *fs) {
    // Initialize data blocks with random values
    for (int i = 0; i < NUM_BLOCKS; i++) {
        fs->dataBlocks[i] = i * 10; // Simple data (e.g., 10, 20, 30, etc.)
    }

    // Initialize index block to -1 (indicating no block allocated)
    for (int i = 0; i < NUM_BLOCKS; i++) {
        fs->indexBlock[i] = -1;
    }
}

// Function to allocate blocks for a file
void allocateFile(FileSystem *fs, int *fileData, int fileSize) {
    // Ensure the file size does not exceed the maximum file size
    if (fileSize > MAX_FILE_SIZE) {
        printf("File size exceeds maximum limit.\n");
        return;
    }

    // Allocate data blocks for the file
    for (int i = 0; i < fileSize; i++) {
        // Simulate allocation by using index block entries
        fs->indexBlock[i] = i; // Point to the corresponding data block
    }

    printf("File allocated successfully.\n");
}

// Function to read a file from the file system
void readFile(FileSystem *fs, int fileSize) {
    printf("Reading file:\n");

    // Read each data block using the index block entries
    for (int i = 0; i < fileSize; i++) {
        if (fs->indexBlock[i] != -1) {
            printf("Block %d: Data = %d\n", i, fs->dataBlocks[fs->indexBlock[i]]);
        } else {
            printf("Block %d: Not allocated\n", i);
        }
    }
}

// Main function to simulate file allocation
int main() {
    FileSystem fs;
    int fileData[MAX_FILE_SIZE] = {1, 2, 3, 4, 5};  // Sample file data
    int fileSize = 3;  // File size (in blocks)

    // Initialize the file system
    initializeFileSystem(&fs);

    // Allocate file
    allocateFile(&fs, fileData, fileSize);

    // Read the file
    readFile(&fs, fileSize);

    return 0;
}

