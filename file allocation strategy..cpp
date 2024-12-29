#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum size for the file
#define MAX_RECORDS 100

// Structure to represent a file record
typedef struct {
    int recordNumber;
    char data[100];  // You can adjust the size as per your needs
} FileRecord;

// Function to simulate writing a record to the file (array of records)
void writeRecord(FileRecord file[], int index, int recordNumber, const char *data) {
    file[index].recordNumber = recordNumber;
    strncpy(file[index].data, data, sizeof(file[index].data) - 1);
    file[index].data[sizeof(file[index].data) - 1] = '\0'; // Ensure null termination
}

// Function to simulate reading a record from the file
void readRecord(FileRecord file[], int index) {
    if (index >= 0 && index < MAX_RECORDS && file[index].recordNumber != 0) {
        printf("Record #%d: %s\n", file[index].recordNumber, file[index].data);
    } else {
        printf("Record not found or index is out of range.\n");
    }
}

// Function to simulate reading the file from the beginning
void readAllRecords(FileRecord file[]) {
    printf("Reading all records:\n");
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (file[i].recordNumber != 0) {  // If the record exists
            printf("Record #%d: %s\n", file[i].recordNumber, file[i].data);
        }
    }
}

// Main function to simulate file operations
int main() {
    // Initialize an array to represent the file records
    FileRecord file[MAX_RECORDS] = {0};

    // Writing records to the file
    writeRecord(file, 0, 1, "First record");
    writeRecord(file, 1, 2, "Second record");
    writeRecord(file, 2, 3, "Third record");

    // Reading specific records
    printf("Reading specific record 1:\n");
    readRecord(file, 0);
    
    printf("\nReading specific record 2:\n");
    readRecord(file, 1);

    // Reading all records from the file
    readAllRecords(file);

    return 0;
}

