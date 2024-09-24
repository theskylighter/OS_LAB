#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int count = 0;
// int i;
// if 'i' is global then almost ~5million, wrong ans

pthread_mutex_t mutex;
void* sum() {
    // if 'i' is local then correct ans , 20M
    int i;
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
// ------------------
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
// Problem with the Global 'i':

    // All four threads are using the same global variable i to control their loops.
    //  As the threads run concurrently, they will interfere with each other's updates to i.
    //   This causes unpredictable behavior, as each thread will change the loop counter for the others,
    //    resulting in incorrect or inconsistent iterations.

    // // Since the for (i = 0; i < 5000000; i++) loop relies on i, the threads will not perform the correct number of iterations.
    //  The behavior of i will be corrupted as multiple threads try to increment it at the same time.