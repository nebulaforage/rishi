#include <stdio.h>

#define MAX_FRAMES 3 // Number of frames in memory

// Function to find the index of the first occurrence of a page in the memory array
int findPageIndex(int frames[], int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == page) {
            return i;
        }
    }
    return -1;
}

// Function to simulate FIFO page replacement
void fifoPageReplacement(int pages[], int numPages) {
    int frames[MAX_FRAMES] = {-1, -1, -1}; // Initializing the memory frames
    int pageFaults = 0;
    int front = 0; // Points to the index of the next frame to replace

    printf("Page reference string: ");
    for (int i = 0; i < numPages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    for (int i = 0; i < numPages; i++) {
        int page = pages[i];
        int index = findPageIndex(frames, page);

        // Page fault occurs if the page is not found in memory
        if (index == -1) {
            // Replace the page in the FIFO manner
            frames[front] = page;
            front = (front + 1) % MAX_FRAMES; // Update front for the next replacement
            pageFaults++;

            printf("\nPage Fault! Replaced page: %d\n", page);
            printf("Frames: ");
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] != -1) {
                    printf("%d ", frames[j]);
                } else {
                    printf("- "); // Indicating an empty frame
                }
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    // Define the page reference string (sequence of page requests)
    int pages[] = {1, 2, 3, 2, 1, 5, 2, 3, 1, 4};
    int numPages = sizeof(pages) / sizeof(pages[0]);

    // Simulate FIFO page replacement
    fifoPageReplacement(pages, numPages);

    return 0;
}

