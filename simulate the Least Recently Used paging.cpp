#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 10  // Maximum number of pages in the memory

// Function to find the least recently used page
int findLRU(int pages[], int n, int pageFrame[], int numFrames) {
    int i, j;
    int leastRecentlyUsed = -1;
    int indexToReplace = -1;
    
    // Initialize the last used times for all frames
    for (i = 0; i < numFrames; i++) {
        int lastUsedTime = -1;
        for (j = n - 1; j >= 0; j--) {
            if (pages[j] == pageFrame[i]) {
                lastUsedTime = j;
                break;
            }
        }
        if (lastUsedTime < leastRecentlyUsed || leastRecentlyUsed == -1) {
            leastRecentlyUsed = lastUsedTime;
            indexToReplace = i;
        }
    }
    return indexToReplace;
}

void LRU(int pages[], int numPages, int numFrames) {
    int pageFrame[numFrames];  // Store frames in memory
    int pageFaults = 0;
    int i, j;
    
    // Initialize all frames as -1 (empty)
    for (i = 0; i < numFrames; i++) {
        pageFrame[i] = -1;
    }

    for (i = 0; i < numPages; i++) {
        int page = pages[i];
        int pageFound = 0;

        // Check if the page is already in memory
        for (j = 0; j < numFrames; j++) {
            if (pageFrame[j] == page) {
                pageFound = 1;
                break;
            }
        }

        // If the page is not found in memory, it is a page fault
        if (!pageFound) {
            pageFaults++;
            
            // Find the least recently used page and replace it
            int lruIndex = findLRU(pages, i, pageFrame, numFrames);
            pageFrame[lruIndex] = page;
        }

        // Print the page frames after each page reference
        printf("Page Reference: %d\tFrames: ", page);
        for (j = 0; j < numFrames; j++) {
            if (pageFrame[j] == -1) {
                printf(" - ");
            } else {
                printf(" %d ", pageFrame[j]);
            }
        }
        printf("\n");
    }

    // Print the total number of page faults
    printf("Total page faults: %d\n", pageFaults);
}

int main() {
    int numFrames, numPages;
    
    printf("Enter the number of frames in memory: ");
    scanf("%d", &numFrames);

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int pages[numPages];
    
    printf("Enter the page reference string: ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Call the LRU simulation function
    LRU(pages, numPages, numFrames);

    return 0;
}

