#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>   // For open()
#include <unistd.h>  // For read(), write(), and close()

#define BUFFER_SIZE 1024

int main() {
    char sourceFile[100], destFile[100];
    int sourceFD, destFD, bytesRead;
    char buffer[BUFFER_SIZE];

    // Input source and destination file names
    printf("Enter the source file name: ");
    scanf("%s", sourceFile);
    printf("Enter the destination file name: ");
    scanf("%s", destFile);

    // Open the source file for reading
    sourceFD = open(sourceFile, O_RDONLY);
    if (sourceFD < 0) {
        perror("Error opening source file");
        return 1;
    }

    // Open/create the destination file for writing
    destFD = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFD < 0) {
        perror("Error opening/creating destination file");
        close(sourceFD);
        return 1;
    }

    // Copy data from source to destination
    while ((bytesRead = read(sourceFD, buffer, BUFFER_SIZE)) > 0) {
        if (write(destFD, buffer, bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            close(sourceFD);
            close(destFD);
            return 1;
        }
    }

    if (bytesRead < 0) {
        perror("Error reading from source file");
    }

    // Close the file descriptors
    close(sourceFD);
    close(destFD);

    printf("File copied successfully!\n");
    return 0;
}

