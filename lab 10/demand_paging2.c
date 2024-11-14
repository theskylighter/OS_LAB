#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomNumbers(int numbers[], int count) {
    for (int i = 0; i < count; i++) {
        numbers[i] = (rand() % 10) + 1;
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

int pageFaultsLRU(int pages[], int n, int capacity) {
    int *frames = (int*)malloc(capacity * sizeof(int));
    int *used = (int*)malloc(capacity * sizeof(int));
    int page_faults = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        used[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                used[j] = i;
                printf("\nPage %d found in LRU", page);
                printState(frames, capacity);
                break;
            }
        }

        if (!found) {
            int lru = 0;
            for (int j = 1; j < capacity; j++) {
                if (used[j] < used[lru]) lru = j;
            }
            printf("\nPage %d not found, page %d replaced with page %d in LRU", page, frames[lru], page);
            frames[lru] = page;
            used[lru] = i;
            page_faults++;
            printState(frames, capacity);
        }
    }
    free(frames);
    free(used);
    return page_faults;
}

int pageFaultsOptimal(int pages[], int n, int capacity) {
    int *frames = (int*)malloc(capacity * sizeof(int));
    int page_faults = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                printf("\nPage %d found in Optimal", page);
                printState(frames, capacity);
                break;
            }
        }

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
    free(frames);
    return page_faults;
}

int pageFaultsMRU(int pages[], int n, int capacity) {
    int *frames = (int*)malloc(capacity * sizeof(int));
    int page_faults = 0;
    int most_recently_used = -1;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                most_recently_used = j;
                printf("\nPage %d found in MRU", page);
                printState(frames, capacity);
                break;
            }
        }

        if (!found) {
            int replaceIndex = most_recently_used == -1 ? 0 : most_recently_used;
            printf("\nPage %d not found, page %d replaced with page %d in MRU", page, frames[replaceIndex], page);
            frames[replaceIndex] = page;
            most_recently_used = replaceIndex;
            page_faults++;
            printState(frames, capacity);
        }
    }
    free(frames);
    return page_faults;
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    generateRandomNumbers(pages, n);

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    // printf("\nTotal page faults using FIFO: %d\n", pageFaultsFIFO(pages, n, capacity));
    printf("\nTotal page faults using LRU: %d\n", pageFaultsLRU(pages, n, capacity));
    printf("\nTotal page faults using Optimal: %d\n", pageFaultsOptimal(pages, n, capacity));
    printf("\nTotal page faults using MRU: %d\n", pageFaultsMRU(pages, n, capacity));

    return 0;
}
