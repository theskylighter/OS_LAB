#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// global variables
    int count = 0;
    int i;
    lock=0;
//-----------

void* routine() {
    for (i = 0; i < 100000; i++) {
       if(lock==0)
        {
            lock=1;
            count++;
            lock=0;
        }
    }
}

int main(int argc, char* argv[]) {
    pthread_t p1, p2, p3, p4;
    if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&p2, NULL, &routine, NULL) != 0) {
        return 2;
    }
    if (pthread_create(&p3, NULL, &routine, NULL) != 0) {
        return 3;
    }
    if (pthread_create(&p4, NULL, &routine, NULL) != 0) {
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
    printf("The value of count is %d\n", count);
    return 0;
}
