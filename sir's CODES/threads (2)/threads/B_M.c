#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define THREAD_NUM 8

pthread_mutex_t mutex;
sem_t semFuel;
int fuel = 50;

void* fun1(void* args) {
    //while (1) {
        pthread_mutex_lock(&mutex);
        printf("Inside thread 1\n");
  //  }
}

void* fun2(void* args) {
    //while (1) {
      //  printf("Inside thread 2 \n");
        pthread_mutex_unlock(&mutex);
        printf("Inside thread 2 \n");
   // }
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    sem_init(&semFuel, 0, 1);
    pthread_mutex_init(&mutex, NULL);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (i % 2 == 0) {
            if (pthread_create(&th[i], NULL, &fun1, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &fun2, NULL) != 0) {
                perror("Failed to create thread");
            }   
        }
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&semFuel);
    return 0;
}
