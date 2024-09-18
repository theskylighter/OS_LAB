#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#define THREAD_NUM 2
pthread_mutex_t mutex_b;
sem_t Empty;
sem_t Full;
int buffer[10];
int count = 0;
void* producer(void* args) {
        while(1)
        {
        int x = rand() % 100;
        // Add to the buffer
        sem_wait(&Empty);
        pthread_mutex_lock(&mutex_b);
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutex_b);
        sem_post(&Full);
         printf("Produced one slot \n");
	}
}

void* consumer(void* args) 
{
	 while(1) 
	 {  
        int y;
		 sem_wait(&Full);
         pthread_mutex_lock(&mutex_b);
          y = buffer[count - 1];
         count--;
        pthread_mutex_unlock(&mutex_b);
        sem_post(&Empty);
        printf("Consumed one slot, Got %d\n", y);
        sleep(1);
}
    }

int main(int argc, char* argv[]) {
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutex_b, NULL);
    sem_init(&Empty, 0, 10);
    sem_init(&Full, 0, 0);
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
    sem_destroy(&Empty);
    sem_destroy(&Full);
    pthread_mutex_destroy(&mutex_b);
    return 0;
}
