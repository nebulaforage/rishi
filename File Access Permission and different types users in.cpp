#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

using namespace std;

// Function to display file permissions
void display_permissions(mode_t mode) {
    // Display file permissions in rwx format
    cout << "File permissions: ";
    
    // Owner permissions
    cout << ((mode & S_IRUSR) ? "r" : "-");
    cout << ((mode & S_IWUSR) ? "w" : "-");
    cout << ((mode & S_IXUSR) ? "x" : "-");
    
    // Group permissions
    cout << ((mode & S_IRGRP) ? "r" : "-");
    cout << ((mode & S_IWGRP) ? "w" : "-");
    cout << ((mode & S_IXGRP) ? "x" : "-");
    
    // Others permissions
    cout << ((mode & S_IROTH) ? "r" : "-");
    cout << ((mode & S_IWOTH) ? "w" : "-");
    cout << ((mode & S_IXOTH) ? "x" : "-");
    
    cout << endl;
}

// Function to check file type and user
void check_file_info(const char* file_name) {
    struct stat file_stat;
    
    if (stat(file_name, &file_stat) == -1) {
        perror("Error getting file information");
        return;
    }

    // Display file type
    if (S_ISDIR(file_stat.st_mode)) {
        cout << file_name << " is a directory" << endl;
    } else if (S_ISREG(file_stat.st_mode)) {
        cout << file_name << " is a regular file" << endl;
    } else if (S_ISLNK(file_stat.st_mode)) {
        cout << file_name << " is a symbolic link" << endl;
    } else {
        cout << file_name << " is another type of file" << endl;
    }
    
    // Display file owner and group
    cout << "File owner: UID " << file_stat.st_uid << endl;
    cout << "File group: GID " << file_stat.st_gid << endl;

    // Display file permissions
    display_permissions(file_stat.st_mode);
}

int main() {
    const char* file_name = "example.txt";  // Change to your file name
    check_file_info(file_name);
    
    return 0;
}

