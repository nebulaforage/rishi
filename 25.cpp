#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // 1. fcntl: File control operations
    int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file with fcntl");
        return 1;
    }
    printf("File opened with file descriptor: %d\n", fd);
    
    // Lock file using fcntl
    struct flock lock;
    lock.l_type = F_WRLCK;  // Set write lock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;  // Lock the entire file
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error locking file");
        close(fd);
        return 1;
    }
    printf("File locked with fcntl.\n");

    // 2. lseek: Move file pointer
    off_t offset = lseek(fd, 10, SEEK_SET);  // Move to 10th byte in file
    if (offset == -1) {
        perror("Error with lseek");
        close(fd);
        return 1;
    }
    printf("Moved file pointer to byte: %lld\n", (long long) offset);

    // 3. stat: Get file status
    struct stat file_stat;
    if (stat("example.txt", &file_stat) == -1) {
        perror("Error getting file stats");
        close(fd);
        return 1;
    }
    printf("File size: %lld bytes\n", (long long) file_stat.st_size);

    // 4. opendir and readdir: Directory operations
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        close(fd);
        return 1;
    }

    struct dirent *entry;
    printf("Reading directory contents:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("Name: %s\n", entry->d_name);
    }
    closedir(dir);
    printf("Directory closed.\n");

    // Clean up and close the file
    close(fd);
    printf("File closed.\n");

    return 0;
}

