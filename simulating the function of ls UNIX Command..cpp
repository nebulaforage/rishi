#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main() {
    struct dirent *entry;
    DIR *dp;

    // Open the current directory
    dp = opendir(".");
    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    // Read and print each entry in the directory
    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dp);

    return 0;
}

