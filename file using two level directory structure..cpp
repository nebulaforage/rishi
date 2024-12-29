#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIRS 10
#define MAX_FILES 10
#define NAME_LEN 50

typedef struct {
    char fileName[NAME_LEN];
} File;

typedef struct {
    char dirName[NAME_LEN];
    File files[MAX_FILES];
    int fileCount;
} Directory;

Directory directories[MAX_DIRS];
int dirCount = 0;

void createDirectory() {
    if (dirCount >= MAX_DIRS) {
        printf("Error: Maximum directory limit reached.\n");
        return;
    }
    printf("Enter directory name: ");
    char dirName[NAME_LEN];
    scanf("%s", dirName);

    for (int i = 0; i < dirCount; i++) {
        if (strcmp(directories[i].dirName, dirName) == 0) {
            printf("Error: Directory already exists.\n");
            return;
        }
    }

    strcpy(directories[dirCount].dirName, dirName);
    directories[dirCount].fileCount = 0;
    dirCount++;
    printf("Directory '%s' created successfully.\n", dirName);
}

void addFile() {
    printf("Enter directory name: ");
    char dirName[NAME_LEN];
    scanf("%s", dirName);

    int dirIndex = -1;
    for (int i = 0; i < dirCount; i++) {
        if (strcmp(directories[i].dirName, dirName) == 0) {
            dirIndex = i;
            break;
        }
    }

    if (dirIndex == -1) {
        printf("Error: Directory not found.\n");
        return;
    }

    if (directories[dirIndex].fileCount >= MAX_FILES) {
        printf("Error: Maximum file limit reached in this directory.\n");
        return;
    }

    printf("Enter file name: ");
    char fileName[NAME_LEN];
    scanf("%s", fileName);

    for (int i = 0; i < directories[dirIndex].fileCount; i++) {
        if (strcmp(directories[dirIndex].files[i].fileName, fileName) == 0) {
            printf("Error: File already exists in the directory.\n");
            return;
        }
    }

    strcpy(directories[dirIndex].files[directories[dirIndex].fileCount].fileName, fileName);
    directories[dirIndex].fileCount++;
    printf("File '%s' added to directory '%s' successfully.\n", fileName, dirName);
}

void listDirectory() {
    if (dirCount == 0) {
        printf("No directories found.\n");
        return;
    }

    printf("\nDirectory Structure:\n");
    for (int i = 0; i < dirCount; i++) {
        printf("Directory: %s\n", directories[i].dirName);
        if (directories[i].fileCount == 0) {
            printf("  (No files)\n");
        } else {
            for (int j = 0; j < directories[i].fileCount; j++) {
                printf("  File: %s\n", directories[i].files[j].fileName);
            }
        }
    }
    printf("\n");
}

int main() {
    int choice;
    while (1) {
        printf("Two-Level Directory Structure\n");
        printf("1. Create Directory\n");
        printf("2. Add File to Directory\n");
        printf("3. List Directories and Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createDirectory();
                break;
            case 2:
                addFile();
                break;
            case 3:
                listDirectory();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

