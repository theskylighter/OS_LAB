#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int count = 0;
pthread_mutex_t mutex;
int i;
void* sum() {
    for (i = 0; i < 5000000; i++) {
       pthread_mutex_lock(&mutex);
        count++;
       pthread_mutex_unlock(&mutex);
    }
}
int main(int argc, char* argv[]) {
    pthread_t p1, p2, p3, p4;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&p1, NULL, &sum, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&p2, NULL, &sum, NULL) != 0) {
        return 2;
    }
    if (pthread_create(&p3, NULL, &sum, NULL) != 0) {
        return 3;
    }
    if (pthread_create(&p4, NULL, &sum, NULL) != 0) {
        return 4;
    }
    if (pthread_join(p1, NULL) != 0) {
        return 5;
    }
    if (pthread_join(p2, NULL) != 0) {
        return 6;
    }
    if (pthread_join(p3, NULL) != 0) {
        return 7;
    }
    if (pthread_join(p4, NULL) != 0) {
        return 8;
    }
    pthread_mutex_destroy(&mutex);
    printf("The value of count is : %d\n", count);
    return 0;
}
