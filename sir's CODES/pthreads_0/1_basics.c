#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* fun1() {
    
    printf("Starting of thread\n");
    sleep(2);
    printf("Ending thread\n");
}
int main(int argc, char* argv[]) {
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, &fun1, NULL);

    pthread_create(&t2, NULL, &fun1, NULL);
   
    pthread_create(&t3, NULL, &fun1, NULL);

    pthread_join(t1, NULL) ;
    pthread_join(t2, NULL) ;
    pthread_join(t3, NULL) ;   
    return 0;

}     