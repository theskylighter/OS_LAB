#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define THREAD_NUM 4
pthread_mutex_t mutexT;
int tawa_roti = 10;
pthread_mutex_t mutexB;
int besan_roti = 5;
void* dead_l(void* args) {
    int index = *(int*)args;
      if (index % 2== 0) {
        pthread_mutex_lock(&mutexT);
	  // sleep(2);
        pthread_mutex_lock(&mutexB);
      } else {
          pthread_mutex_lock(&mutexB);
       // sleep(1);
        pthread_mutex_lock(&mutexT);
    }
    tawa_roti += 10;
    besan_roti += 5;
    printf(" Got roties: Now I have %d Tawa Roti  and %d Besan Roti \n", tawa_roti, besan_roti);
    pthread_mutex_unlock(&mutexT);
    pthread_mutex_unlock(&mutexB);
}
int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexT, NULL);
    pthread_mutex_init(&mutexB, NULL);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
    	int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &dead_l, a) != 0) {
            perror("Failed to create thread");
        }
    }
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    printf("Tawa Roti: %d\n", tawa_roti);
    printf("Besan Roti: %d\n", besan_roti);
    pthread_mutex_destroy(&mutexT);
    pthread_mutex_destroy(&mutexB);
    return 0;
}
