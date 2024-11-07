#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomNumbers(int numbers[], int count) {
    for (int i = 0; i < count; i++) {
        numbers[i] = (rand() % 10) + 1;
        printf("%d ",numbers[i]);
        }
    printf("\n");    
}

void printState(int frames[],int n, int capacity){
    printf("\n");
    for(int i=0;i<capacity;i++){
        printf("%d  ",frames[i]);
    }
}

int pageFaultsFIFO(int pages[], int n, int capacity) {
    int frames[capacity];
    int front = 0; 
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
                printf("\nPage %d found, no changes in frame",page);
                printState(frames,n,capacity);
                break;
            }
        }

        if (!found) {
            printf("\nPage %d not found, page %d replaced with page %d",page,frames[front],page);
            frames[front] = page;  
            front = (front + 1) % capacity; 
            page_faults++;
            printf("\nFrame state after replacement:");
            printState(frames,n,capacity);
            }
    }

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

    int result = pageFaultsFIFO(pages, n, capacity);
    printf("Total page faults using FIFO: %d\n", result);

    return 0;
}