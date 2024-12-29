#include <stdio.h>

// Function to calculate waiting time
void calculateWaitingTime(int processes[], int n, int burstTime[], int waitingTime[]) {
    waitingTime[0] = 0; // First process has 0 waiting time

    for (int i = 1; i < n; i++) {
        waitingTime[i] = burstTime[i - 1] + waitingTime[i - 1];
    }
}

// Function to calculate turnaround time
void calculateTurnaroundTime(int processes[], int n, int burstTime[], int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }
}

// Function to display the process details
void displayProcessDetails(int processes[], int n, int burstTime[], int waitingTime[], int turnaroundTime[]) {
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }
}

int main() {
    int n;

    // Input: Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burstTime[n], waitingTime[n], turnaroundTime[n];

    // Input: Burst time for each process
    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1; // Process IDs
        printf("Burst time for process P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    // Calculate waiting and turnaround times
    calculateWaitingTime(processes, n, burstTime, waitingTime);
    calculateTurnaroundTime(processes, n, burstTime, waitingTime, turnaroundTime);

    // Display the process details
    printf("\n--- First-Come, First-Served (FCFS) Scheduling ---\n");
    displayProcessDetails(processes, n, burstTime, waitingTime, turnaroundTime);

    // Calculate and display average waiting and turnaround times
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);

    return 0;
}
//Enter the number of processes: 3
//Enter the burst time for each process:
//Burst time for process P1: 5
//Burst time for process P2: 8
//Burst time for process P3: 12

