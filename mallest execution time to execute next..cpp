#include <stdio.h>

void sortProcesses(int n, int processes[], int burstTime[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (burstTime[j] > burstTime[j + 1]) {
                // Swap burst times
                int temp = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = temp;

                // Swap process IDs
                int tempID = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = tempID;
            }
        }
    }
}

void calculateWaitingTime(int n, int burstTime[], int waitingTime[]) {
    waitingTime[0] = 0; // First process has no waiting time

    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    }
}

void calculateTurnaroundTime(int n, int burstTime[], int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }
}

void displayProcessDetails(int n, int processes[], int burstTime[], int waitingTime[], int turnaroundTime[]) {
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

    // Sort processes by burst time
    sortProcesses(n, processes, burstTime);

    // Calculate waiting and turnaround times
    calculateWaitingTime(n, burstTime, waitingTime);
    calculateTurnaroundTime(n, burstTime, waitingTime, turnaroundTime);

    // Display the process details
    printf("\n--- Shortest Job First (SJF) Scheduling ---\n");
    displayProcessDetails(n, processes, burstTime, waitingTime, turnaroundTime);

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

