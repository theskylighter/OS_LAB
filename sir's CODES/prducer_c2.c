#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#define THREAD_NUM 2
int buffer[10];
int count = 0;
void* producer(void* args) {
        while(1)
        {
        int x = rand() % 100;
        // Add to the buffer
        buffer[count] = x;
        count++;
    }
}

void* consumer(void* args) {
	 while(1) 
	 {  
        int y;
        // Remove from the buffer
        y = buffer[count - 1];
        count--;
        // Consume
        printf("Got %d\n", y);
    }
    }
int main(int argc, char* argv[]) {
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&buffer, NULL);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (i > 0) {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    
    pthread_mutex_destroy(&buffer);
    return 0;
}
