#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int count = 0;
int i;
pthread_mutex_t mutex;
void* fun1() {
	sleep(2);
	printf("Hi i am inside Function \n");
  //  for (i = 0; i < 100; i++) {
   //     pthread_mutex_lock(&mutex);
   //     count++;
   //     pthread_mutex_unlock(&mutex);
    }
//}

int main(int argc, char* argv[]) {
    pthread_t th[8];
    int i;
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 8; i++) {
        if (pthread_create(th + i, NULL, &fun1, NULL) != 0) {
            printf("Some error occured, Failed to create");
            return 1;
        }
        printf("Thread %d has started\n", i);
 //      pthread_join(th[i], NULL);
       
 //      printf("Thread %d has finished execution\n", i);
        }
    for(i = 0; i < 8; i++) {
       pthread_join(th[i], NULL);
     printf("Thread %d has finished execution\n", i);
        }
    pthread_mutex_destroy(&mutex);
    printf("The value of count is: %d\n", count);
    return 0;
}
