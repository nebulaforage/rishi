#include <stdio.h>

void FCFS(int arr[], int n, int head) {
    int total_seek_count = 0;
    int seek_count = 0;
    int distance, cur_head;

    // Loop through all the requests
    cur_head = head;
    for (int i = 0; i < n; i++) {
        distance = abs(arr[i] - cur_head);
        seek_count += distance;
        cur_head = arr[i];
        printf("Head moves from %d to %d with seek distance = %d\n", cur_head - distance, cur_head, distance);
    }

    total_seek_count = seek_count;
    printf("Total Seek Count: %d\n", total_seek_count);
    printf("Average Seek Count: %.2f\n", (float)total_seek_count / n);
}

int main() {
    int n, head;
    
    // Taking number of requests and initial head position
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    // Calling FCFS function to simulate the disk scheduling
    FCFS(arr, n, head);

    return 0;
}

