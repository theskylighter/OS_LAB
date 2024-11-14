#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomNumbers(int numbers[], int count) {
    for (int i = 0; i < count; i++) {
        numbers[i] = (rand() % 10) + 1;  // Random number between 1 and 10
        printf("%d ", numbers[i]);
    }
    printf("\n");    
}

void printState(int frames[], int capacity) {
    printf("\n");
    for (int i = 0; i < capacity; i++) {
        printf("%d  ", frames[i]);
    }
    printf("\n");
}

int pageFaultsFIFO(int pages[], int n, int capacity) {
    int frames[capacity];
    int front = 0;
    int page_faults = 0;

    // Initialize frames with -1 (empty)
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    // Process each page
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                printf("\nPage %d found, no changes in frame", page);
                printState(frames, capacity);
                break;
            }
        }

        // If not found, replace the page in the frame using FIFO
        if (!found) {
            printf("\nPage %d not found, page %d replaced with page %d", page, frames[front], page);
            frames[front] = page;
            front = (front + 1) % capacity;
            page_faults++;
            printf("\nFrame state after replacement:");
            printState(frames, capacity);
        }
    }
    return page_faults;
}

int pageFaultsLRU(int pages[], int n, int capacity) {
    int frames[capacity];
    int used[capacity];
    int page_faults = 0;

    // Initialize frames and used arrays
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        used[i] = -1;
    }

    // Process each page
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                used[j] = i;  // Update the last used time
                printf("\nPage %d found in LRU", page);
                printState(frames, capacity);
                break;
            }
        }

        // If not found, replace the page using LRU
        if (!found) {
            int lru = 0;
            for (int j = 1; j < capacity; j++) {
                if (used[j] < used[lru]) lru = j;  // Find the least recently used page
            }
            printf("\nPage %d not found, page %d replaced with page %d in LRU", page, frames[lru], page);
            frames[lru] = page;
            used[lru] = i;  // Update last used time
            page_faults++;
            printState(frames, capacity);
        }
    }
    return page_faults;
}

int pageFaultsOptimal(int pages[], int n, int capacity) {
    int frames[capacity];
    int page_faults = 0;

    // Initialize frames
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    // Process each page
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                printf("\nPage %d found in Optimal", page);
                printState(frames, capacity);
                break;
            }
        }

        // If not found, replace the page using Optimal page replacement strategy
        if (!found) {
            int replaceIndex = -1, farthest = i + 1;
            for (int j = 0; j < capacity; j++) {
                int nextUse = -1;
                for (int k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        nextUse = k;
                        break;
                    }
                }
                if (nextUse == -1) {
                    replaceIndex = j;
                    break;
                }
                if (nextUse > farthest) {
                    farthest = nextUse;
                    replaceIndex = j;
                }
            }
            printf("\nPage %d not found, page %d replaced with page %d in Optimal", page, frames[replaceIndex], page);
            frames[replaceIndex] = page;
            page_faults++;
            printState(frames, capacity);
        }
    }
    return page_faults;
}

int pageFaultsMRU(int pages[], int n, int capacity) {
    int frames[capacity];
    int most_recently_used = -1;
    int page_faults = 0;

    // Initialize frames
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    // Process each page
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                most_recently_used = j;  // Update the most recently used page
                printf("\nPage %d found in MRU", page);
                printState(frames, capacity);
                break;
            }
        }

        // If not found, replace the page using MRU strategy
        if (!found) {
            int replaceIndex = most_recently_used == -1 ? 0 : most_recently_used;
            printf("\nPage %d not found, page %d replaced with page %d in MRU", page, frames[replaceIndex], page);
            frames[replaceIndex] = page;
            most_recently_used = replaceIndex;
            page_faults++;
            printState(frames, capacity);
        }
    }
    return page_faults;
}

int main() {
    int n, capacity;

    // Take input for number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    generateRandomNumbers(pages, n);

    // Take input for the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    // Output total page faults for each replacement algorithm
    printf("\nTotal page faults using FIFO: %d\n", pageFaultsFIFO(pages, n, capacity));
    printf("\nTotal page faults using LRU: %d\n", pageFaultsLRU(pages, n, capacity));
    printf("\nTotal page faults using Optimal: %d\n", pageFaultsOptimal(pages, n, capacity));
    printf("\nTotal page faults using MRU: %d\n", pageFaultsMRU(pages, n, capacity));

    return 0;
}
