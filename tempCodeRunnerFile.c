#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define limit 5
#define TCOUNT 10

int count = 0;
pthread_mutex_t lock;
pthread_cond_t cond;

void* increment(void* arg){
    
    for(int i = 0; i < TCOUNT; i++){
        pthread_mutex_lock(&lock);

        count++;
        printf("Incrementing thread, incrementing count = %d\n", count);

        if (count == limit) {
            pthread_cond_signal(&cond);
        }

        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

void* watcher(void* arg){
    while(count < TCOUNT){
        pthread_mutex_lock(&lock);
    
        pthread_cond_wait(&cond, &lock);

        //modify sum in a diff way
        count *= 10;
        printf("Watcher thread, count multiplied by 10: %d\n", count);

        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

int main(){

    pthread_t threads[3];
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);

    for(int i = 0; i < 2; i++){
        if(pthread_create(&threads[i], NULL, increment, NULL)){
            perror("Thread creation failed");
            return 1;
        }
    }

    if(pthread_create(&threads[2], NULL, watcher, NULL)){
        perror("Thread creation failed");
        return 1;
    }

    for(int i = 0; i < 3; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Main thread, final value of count: %d\n",count);
    pthread_exit(NULL);
}