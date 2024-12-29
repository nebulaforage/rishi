#include <stdio.h>
#include <fcntl.h>   // For open()
#include <unistd.h>  // For write(), read(), close()
#include <string.h>  // For strlen()

int main() {
    // File paths
    char *filename = "example_file.txt";
    int fd;
    
    // Open the file for writing (create it if it does not exist)
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);  // rw for the user
    if (fd == -1) {
        perror("Error opening file for writing");
        return 1;
    }
    printf("File '%s' opened successfully for writing.\n", filename);

    // Write data to the file
    char *data = "Hello, this is a demonstration of UNIX system calls for file management!";
    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    printf("Data written to file: %zd bytes\n", bytes_written);

    // Close the file after writing
    if (close(fd) == -1) {
        perror("Error closing file after writing");
        return 1;
    }

    // Open the file for reading
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }
    printf("File '%s' opened successfully for reading.\n", filename);

    // Read the data from the file
    char buffer[256];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);  // Leave space for null-terminator
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }
    buffer[bytes_read] = '\0';  // Null-terminate the string
    printf("Data read from file: %s\n", buffer);

    // Close the file after reading
    if (close(fd) == -1) {
        perror("Error closing file after reading");
        return 1;
    }

    return 0;
}

