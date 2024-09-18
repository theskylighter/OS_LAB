#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
int arr[11] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 30 };
int i;
void* fun1(void* arg) {
    int index = *(int*)arg;
 //   sleep(2);
    printf("%d ", arr[index]);
}
int main(int argc, char* argv[]) {
    pthread_t th[10];
    int i,j;
    for (i = 0; i <10; i++) {
        if (pthread_create(&th[i], NULL, &fun1, &i) != 0) {
            printf("Failed to created thread");
        }
    }
    for (j = 0; j < 10; j++) {
        if (pthread_join(th[j], NULL) != 0) {
            printf("Failed to join thread");
        }
    }  
    return 0;
}
