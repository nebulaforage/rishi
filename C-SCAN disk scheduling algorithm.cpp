#include <stdio.h>
#include <stdlib.h>

void CS_CAN(int arr[], int size, int head, int disk_size) {
    int distance = 0, cur_track = 0;
    int left[size], right[size];
    int left_count = 0, right_count = 0;

    // Split requests into left and right of the head.
    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left[left_count++] = arr[i];
        else
            right[right_count++] = arr[i];
    }

    // Sort left and right arrays.
    qsort(left, left_count, sizeof(int), (int (*)(const void *, const void *))compare);
    qsort(right, right_count, sizeof(int), (int (*)(const void *, const void *))compare);

    // Run the C-SCAN algorithm.
    // Move right first, then go to the beginning and move left.
    // Calculate distance for right side of the head.
    for (int i = 0; i < right_count; i++) {
        cur_track = right[i];
        distance += abs(cur_track - head);
        head = cur_track;
    }

    // Move to the beginning of the disk.
    head = 0;
    distance += abs(head - disk_size);

    // Now move left side.
    for (int i = left_count - 1; i >= 0; i--) {
        cur_track = left[i];
        distance += abs(cur_track - head);
        head = cur_track;
    }

    // Output total seek time.
    printf("\nTotal Seek Time: %d\n", distance);
}

// Function to compare integers for qsort().
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int disk_size, size, head;

    // Input disk size, number of requests and the initial head position.
    printf("Enter the number of disk positions: ");
    scanf("%d", &disk_size);
    printf("Enter the number of requests: ");
    scanf("%d", &size);
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    int requests[size];

    printf("Enter the disk requests: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &requests[i]);
    }

    // Call CS-CAN function to process the disk scheduling.
    CS_CAN(requests, size, head, disk_size);

    return 0;
}

