#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int count = 0;
void* sum() {
	int i;
    for (i = 0; i <50000; i++) {
        count++;
    }
}
int main(int argc, char* argv[]) {
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &sum, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &sum, NULL) != 0) {
        return 2;
    }
    if (pthread_join(t1, NULL) != 0) {
        return 3;
    }
    if (pthread_join(t2, NULL) != 0) {
        return 4;
    }
    printf("The value of count is : %d\n", count);
    return 0;
}
