#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

typedef struct {
    char name[MAX_FILENAME_LENGTH];
    int is_occupied;
} File;

File directory[MAX_FILES];

void initialize_directory() {
    for (int i = 0; i < MAX_FILES; i++) {
        directory[i].is_occupied = 0;
    }
}

int create_file(char *filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (directory[i].is_occupied && strcmp(directory[i].name, filename) == 0) {
            printf("Error: File '%s' already exists.\n", filename);
            return 0;
        }
    }

    for (int i = 0; i < MAX_FILES; i++) {
        if (!directory[i].is_occupied) {
            strcpy(directory[i].name, filename);
            directory[i].is_occupied = 1;
            printf("File '%s' created successfully.\n", filename);
            return 1;
        }
    }

    printf("Error: Directory is full.\n");
    return 0;
}

int delete_file(char *filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (directory[i].is_occupied && strcmp(directory[i].name, filename) == 0) {
            directory[i].is_occupied = 0;
            printf("File '%s' deleted successfully.\n", filename);
            return 1;
        }
    }

    printf("Error: File '%s' not found.\n", filename);
    return 0;
}

void list_files() {
    printf("Files in the directory:\n");
    int found = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        if (directory[i].is_occupied) {
            printf(" - %s\n", directory[i].name);
            found = 1;
        }
    }
    if (!found) {
        printf(" (No files in the directory)\n");
    }
}

int main() {
    initialize_directory();
    int choice;
    char filename[MAX_FILENAME_LENGTH];

    do {
        printf("\nSingle-Level Directory Menu:\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. List Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the name of the file to create: ");
                scanf("%s", filename);
                create_file(filename);
                break;
            case 2:
                printf("Enter the name of the file to delete: ");
                scanf("%s", filename);
                delete_file(filename);
                break;
            case 3:
                list_files();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

