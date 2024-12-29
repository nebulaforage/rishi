#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[], int tq) {
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = bt[i];
        wt[i] = 0;  // Waiting time initialized to 0
    }

    int time = 0;
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0;
                if (remaining_time[i] > tq) {
                    time += tq;
                    remaining_time[i] -= tq;
                } else {
                    time += remaining_time[i];
                    wt[i] = time - bt[i];  // Calculate waiting time for the process
                    remaining_time[i] = 0;
                }
            }
        }
        if (done == 1) {
            break;  // Exit when all processes are finished
        }
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];  // Turnaround time = burst time + waiting time
    }
}

void findAverageTime(int processes[], int n, int bt[], int tq) {
    int wt[n], tat[n];
    
    findWaitingTime(processes, n, bt, wt, tq);
    findTurnAroundTime(processes, n, bt, wt, tat);
    
    float total_wt = 0, total_tat = 0;
    
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }
    
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
}

int main() {
    int n, tq;
    
    // Take number of processes and time quantum as input
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    int processes[n], burst_time[n];
    
    // Input burst times for all processes
    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
        processes[i] = i + 1;  // Process IDs
    }
    
    // Input time quantum
    printf("Enter time quantum: ");
    scanf("%d", &tq);
    
    // Calculate and display the average waiting time and turnaround time
    findAverageTime(processes, n, burst_time, tq);
    
    return 0;
}

