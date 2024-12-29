#include <stdio.h>

struct Process {
    int pid;       // Process ID
    int bt;        // Burst Time
    int wt;        // Waiting Time
    int tat;       // Turnaround Time
};

void findWaitingTime(struct Process proc[], int n) {
    proc[0].wt = 0;  // First process has no waiting time

    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i - 1].bt + proc[i - 1].wt;
    }
}

void findTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].bt + proc[i].wt;
    }
}

void findAvgTime(struct Process proc[], int n) {
    int total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_tat / n);
}

void sjfScheduling(struct Process proc[], int n) {
    struct Process temp;
    
    // Sort processes based on burst time (Shortest Job First)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].bt > proc[j].bt) {
                // Swap processes
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    // Find waiting time and turnaround time
    findWaitingTime(proc, n);
    findTurnaroundTime(proc, n);

    // Display process details
    printf("\nPID\tBurst Time\tWaiting Time\tTurnaround Time");
    for (int i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t%d\t\t%d", proc[i].pid, proc[i].bt, proc[i].wt, proc[i].tat);
    }

    // Calculate and display average times
    findAvgTime(proc, n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("\nEnter Burst Time for Process %d: ", proc[i].pid);
        scanf("%d", &proc[i].bt);
    }

    // Run the SJF scheduling algorithm
    sjfScheduling(proc, n);

    return 0;
}

