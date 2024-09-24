#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<semaphore.h>
#define THREAD_NUM 8
sem_t semaphore;
void* fun1(void* args) {
    sem_wait(&semaphore);
   sleep(1);
    printf("Hello from thread %d\n", *(int*)args);
    sem_post(&semaphore);
    free(args);
}
int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];

// 0 = semaphore is shared bw the threads of same process 
// 4 = maximum no of th that can access shared resource
    sem_init(&semaphore, 0, 4);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &fun1, a) != 0) {
            perror("Failed to create thread");
        }
    }
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semaphore);
    return 0;
}