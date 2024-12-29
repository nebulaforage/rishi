#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a disk block
typedef struct DiskBlock {
    char data[50]; // Data stored in the block (for simplicity, it's just a string)
    struct DiskBlock* next; // Pointer to the next block (NULL if it's the last block)
} DiskBlock;

// Define a structure for a file (linked list of disk blocks)
typedef struct File {
    DiskBlock* firstBlock; // Pointer to the first block of the file
    DiskBlock* lastBlock;  // Pointer to the last block of the file
} File;

// Function to create a new disk block
DiskBlock* createDiskBlock(const char* data) {
    DiskBlock* newBlock = (DiskBlock*)malloc(sizeof(DiskBlock));
    if (!newBlock) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newBlock->data, data); // Copy data to the block
    newBlock->next = NULL; // Initially, the next pointer is NULL
    return newBlock;
}

// Function to create a new file
File* createFile() {
    File* newFile = (File*)malloc(sizeof(File));
    if (!newFile) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newFile->firstBlock = NULL;
    newFile->lastBlock = NULL;
    return newFile;
}

// Function to add a block to a file
void addBlockToFile(File* file, const char* data) {
    DiskBlock* newBlock = createDiskBlock(data);
    if (file->lastBlock == NULL) {
        // If the file is empty, the first block is also the last block
        file->firstBlock = newBlock;
        file->lastBlock = newBlock;
    } else {
        // Otherwise, append the new block to the last block
        file->lastBlock->next = newBlock;
        file->lastBlock = newBlock;
    }
}

// Function to display the content of the file (the linked blocks)
void displayFile(File* file) {
    if (file->firstBlock == NULL) {
        printf("File is empty.\n");
        return;
    }

    DiskBlock* currentBlock = file->firstBlock;
    while (currentBlock != NULL) {
        printf("Block Data: %s\n", currentBlock->data);
        currentBlock = currentBlock->next;
    }
}

// Function to free the memory used by the file
void freeFile(File* file) {
    DiskBlock* currentBlock = file->firstBlock;
    while (currentBlock != NULL) {
        DiskBlock* temp = currentBlock;
        currentBlock = currentBlock->next;
        free(temp);
    }
    free(file);
}

int main() {
    // Create a file
    File* file = createFile();
    
    // Add blocks to the file
    addBlockToFile(file, "Block 1: Data of the file");
    addBlockToFile(file, "Block 2: More data");
    addBlockToFile(file, "Block 3: Even more data");

    // Display the content of the file (linked blocks)
    printf("Displaying File Content:\n");
    displayFile(file);

    // Free the allocated memory
    freeFile(file);
    
    return 0;
}

