#include <stdio.h>

#define MAX_PROCESSES 100

// Structure to represent a process
typedef struct {
    int id;         // Process ID
    int burst_time; // Burst time
    int priority;   // Priority (lower value = higher priority)
    int waiting_time;
    int turnaround_time;
} Process;

// Function to sort processes by priority (ascending order)
void sort_by_priority(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to calculate waiting and turnaround times
void calculate_times(Process processes[], int n) {
    processes[0].waiting_time = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }

    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

// Function to display process details
void display_processes(Process processes[], int n) {
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", 
            processes[i].id, 
            processes[i].burst_time, 
            processes[i].priority, 
            processes[i].waiting_time, 
            processes[i].turnaround_time);
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];
    float total_waiting_time = 0, total_turnaround_time = 0;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; // Process ID
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for Process P%d (lower value = higher priority): ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    // Sort processes by priority and calculate times
    sort_by_priority(processes, n);
    calculate_times(processes, n);

    // Display process details
    display_processes(processes, n);

    // Calculate and display average times
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);

    return 0;
}

