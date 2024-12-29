#include <stdio.h>
#include <stdlib.h>

void createFile() {
    FILE *file;
    char filename[100];
    char content[1000];

    printf("Enter the name of the file to create: ");
    scanf("%s", filename);

    file = fopen(filename, "w"); // Open for writing
    if (file == NULL) {
        printf("Unable to create the file.\n");
        return;
    }

    printf("Enter content to write to the file (max 1000 characters):\n");
    getchar();  // To consume the newline character left by scanf
    fgets(content, sizeof(content), stdin);

    fprintf(file, "%s", content);
    fclose(file);
    printf("File '%s' created successfully!\n", filename);
}

void readFile() {
    FILE *file;
    char filename[100];
    char ch;

    printf("Enter the name of the file to read: ");
    scanf("%s", filename);

    file = fopen(filename, "r"); // Open for reading
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    printf("Contents of the file '%s':\n", filename);
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

void appendToFile() {
    FILE *file;
    char filename[100];
    char content[1000];

    printf("Enter the name of the file to append: ");
    scanf("%s", filename);

    file = fopen(filename, "a"); // Open for appending
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    printf("Enter content to append to the file (max 1000 characters):\n");
    getchar();  // To consume the newline character left by scanf
    fgets(content, sizeof(content), stdin);

    fprintf(file, "%s", content);
    fclose(file);
    printf("Content appended to file '%s'.\n", filename);
}

void deleteFile() {
    char filename[100];
    printf("Enter the name of the file to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        printf("Unable to delete the file.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nFile Management Operations:\n");
        printf("1. Create a file\n");
        printf("2. Read a file\n");
        printf("3. Append to a file\n");
        printf("4. Delete a file\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                readFile();
                break;
            case 3:
                appendToFile();
                break;
            case 4:
                deleteFile();
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

