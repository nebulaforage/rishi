#include <stdio.h>
#include <stdlib.h>

void SCAN(int arr[], int n, int head, int direction) {
    int left = 0, right = 0, i, j;
    int totalHeadMovement = 0;
    int leftArray[100], rightArray[100];

    // Divide the requests into two parts
    for(i = 0; i < n; i++) {
        if(arr[i] < head)
            leftArray[left++] = arr[i];
        else
            rightArray[right++] = arr[i];
    }

    // Sort the left and right arrays
    for(i = 0; i < left - 1; i++) {
        for(j = i + 1; j < left; j++) {
            if(leftArray[i] < leftArray[j]) {
                int temp = leftArray[i];
                leftArray[i] = leftArray[j];
                leftArray[j] = temp;
            }
        }
    }

    for(i = 0; i < right - 1; i++) {
        for(j = i + 1; j < right; j++) {
            if(rightArray[i] > rightArray[j]) {
                int temp = rightArray[i];
                rightArray[i] = rightArray[j];
                rightArray[j] = temp;
            }
        }
    }

    // Traverse the left side
    if(direction == 0) {
        // Move towards left
        for(i = left - 1; i >= 0; i--) {
            totalHeadMovement += abs(head - leftArray[i]);
            head = leftArray[i];
        }

        // Traverse the right side
        for(i = 0; i < right; i++) {
            totalHeadMovement += abs(head - rightArray[i]);
            head = rightArray[i];
        }
    } else {
        // Move towards right
        for(i = 0; i < right; i++) {
            totalHeadMovement += abs(head - rightArray[i]);
            head = rightArray[i];
        }

        // Traverse the left side
        for(i = left - 1; i >= 0; i--) {
            totalHeadMovement += abs(head - leftArray[i]);
            head = leftArray[i];
        }
    }

    // Display the total head movement
    printf("Total head movement is %d\n", totalHeadMovement);
}

int main() {
    int n, head, direction;
    
    // Input number of requests
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    
    int arr[n];
    
    // Input the disk requests
    printf("Enter the disk requests:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Input the initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    // Input the direction of movement (0 for left, 1 for right)
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    // Call the SCAN function to simulate the disk scheduling
    SCAN(arr, n, head, direction);

    return 0;
}

