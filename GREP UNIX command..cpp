#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void grep(FILE *file, const char *pattern) {
    char line[1024];  // Buffer to hold each line from the file
    
    while (fgets(line, sizeof(line), file)) {
        // Check if the pattern exists in the line
        if (strstr(line, pattern)) {
            printf("%s", line);  // Print the line if it matches the pattern
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <pattern> <file>\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];  // The search pattern
    const char *filename = argv[2]; // The file to search in
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Call the grep function to search for the pattern
    grep(file, pattern);

    fclose(file); // Close the file after processing
    return 0;
}

