#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutex;

void* lock(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Got lock\n");
    sleep(1);
    pthread_mutex_unlock(&mutex);
}

void* trylock(void* arg) {
    if (pthread_mutex_trylock(&mutex) == 0) {
        printf("Got lock\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    } else {
        printf("Didn't get lock\n");
    }
}

int main(int argc, char* argv[]) {
    pthread_t th[4];
    int i;
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 4; i++) {
        if(pthread_create(&th[i], NULL, &trylock, NULL) != 0) {
            perror("Error at creating thread");
        }
    }
    for(i = 0; i < 4; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Error at joining thread");
        }
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}
