#include <stdio.h>

#define MAX_FRAMES 10

// Function to find the index of the page that will not be used for the longest period
int optimalPageReplacement(int pages[], int frames[], int n, int num_frames, int current_index) {
    int farthest = current_index;
    int page_to_replace = -1;

    // For each frame, find the farthest page in future references
    for (int i = 0; i < num_frames; i++) {
        int found = 0;
        // Search for the page in future references
        for (int j = current_index + 1; j < n; j++) {
            if (frames[i] == pages[j]) {
                found = 1;
                if (j > farthest) {
                    farthest = j;
                    page_to_replace = i;
                }
                break;
            }
        }
        // If the page is not found in the future, replace it
        if (!found) {
            return i;
        }
    }
    return page_to_replace;
}

// Function to implement Optimal Page Replacement algorithm
void optimalPageReplacementAlgo(int pages[], int n, int num_frames) {
    int frames[MAX_FRAMES];
    int page_faults = 0;

    // Initialize frames to -1 (empty)
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    printf("Page reference string: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    printf("\nOptimal Page Replacement\n");
    printf("Page\tFrames\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int page_found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                page_found = 1;
                break;
            }
        }

        // If page not found in frames, replace a page
        if (!page_found) {
            int replace_index = -1;

            // If there is an empty frame, place the page
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    replace_index = j;
                    break;
                }
            }

            // If all frames are full, apply optimal replacement
            if (replace_index == -1) {
                replace_index = optimalPageReplacement(pages, frames, n, num_frames, i);
            }

            frames[replace_index] = page;
            page_faults++;
        }

        // Print the frames after each page reference
        printf("%d\t", page);
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal page faults: %d\n", page_faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 0, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int num_frames = 3;

    optimalPageReplacementAlgo(pages, n, num_frames);

    return 0;
}

