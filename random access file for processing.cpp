#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Employee structure
typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

// Function prototypes
void addEmployee(FILE *file);
void displayEmployees(FILE *file);
void searchEmployee(FILE *file);
void updateEmployee(FILE *file);

int main() {
    FILE *file;
    int choice;

    // Open the file in binary read/write mode
    file = fopen("employees.dat", "rb+");
    if (file == NULL) {
        // If the file doesn't exist, create it
        file = fopen("employees.dat", "wb+");
        if (file == NULL) {
            printf("Error: Unable to open or create file.\n");
            return 1;
        }
    }

    do {
        printf("\n--- Employee Management ---\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Update Employee by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                displayEmployees(file);
                break;
            case 3:
                searchEmployee(file);
                break;
            case 4:
                updateEmployee(file);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    fclose(file);
    return 0;
}

// Function to add an employee
void addEmployee(FILE *file) {
    Employee emp;
    fseek(file, 0, SEEK_END); // Move to the end of the file

    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf(" %[^\n]", emp.name);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(Employee), 1, file); // Write to file
    printf("Employee added successfully!\n");
}

// Function to display all employees
void displayEmployees(FILE *file) {
    Employee emp;
    rewind(file); // Move to the beginning of the file

    printf("\n--- Employee Details ---\n");
    while (fread(&emp, sizeof(Employee), 1, file)) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }
}

// Function to search for an employee by ID
void searchEmployee(FILE *file) {
    int id;
    Employee emp;
    int found = 0;

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    rewind(file); // Move to the beginning of the file
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            printf("Employee Found: ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
}

// Function to update an employee by ID
void updateEmployee(FILE *file) {
    int id;
    Employee emp;
    int found = 0;

    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    rewind(file); // Move to the beginning of the file
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            found = 1;
            printf("Enter New Name: ");
            scanf(" %[^\n]", emp.name);
            printf("Enter New Salary: ");
            scanf("%f", &emp.salary);

            fseek(file, -sizeof(Employee), SEEK_CUR); // Move back one record
            fwrite(&emp, sizeof(Employee), 1, file); // Update the record
            printf("Employee updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
}

