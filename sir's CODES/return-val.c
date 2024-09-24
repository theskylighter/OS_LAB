#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
void* fun1() {
    int value = 10;
    int* result;
	result= (int*)malloc(sizeof(int));
    *result = value;
     printf("Inside thread fun1 %d\n", value);
    printf("Thread result: %p\n", result);
   pthread_exit(result);
 //   return (void*) result;
}
int main(int argc, char* argv[]) {
    int* res1;
    pthread_t th;
    if (pthread_create(&th, NULL, &fun1, NULL) != 0) {
        return 1;
    }
    if (pthread_join(th, (void**) &res1) != 0) {
        return 2;
    }
    printf("Main res: %p\n", res1);
    printf("Inside main function Result: %d\n", *res1);
    free(res1);
    return 0;
}
