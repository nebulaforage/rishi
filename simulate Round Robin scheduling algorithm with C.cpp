#include <stdio.h>

void roundRobin(int processes[], int n, int burstTime[], int quantum) {
    int waitingTime[n], turnAroundTime[n], remainingTime[n];
    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    
    // Copy burst times to remaining times
    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
    }

    int t = 0; // Current time
    while (1) {
        int done = 1;
        
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                done = 0; // There is a pending process
                
                if (remainingTime[i] > quantum) {
                    t += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    t += remainingTime[i];
                    waitingTime[i] = t - burstTime[i];
                    remainingTime[i] = 0;
                }
            }
        }
        
        if (done == 1) break; // All processes are done
    }

    // Calculate turn around time
    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = burstTime[i] + waitingTime[i];
    }

    // Display results
    printf("Process\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i], burstTime[i], waitingTime[i], turnAroundTime[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turn Around Time = %.2f\n", (float)totalTurnAroundTime / n);
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burstTime[n];

    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    roundRobin(processes, n, burstTime, quantum);

    return 0;
}

