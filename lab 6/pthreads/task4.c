#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>  // for sleep()

/* function to be executed by the new thread */
void* PrintHello(void* data) {
    int my_data = (int)data; /* safely cast the data received by thread */

    printf("Hello from new thread - got %d\n", my_data);

    // No pthread_exit() here; thread will terminate naturally
    return NULL; /* returning from the function ends the thread */
}

int main(int argc, char* argv[]) {
    int rc; /* return value */
    pthread_t thread_id; /* thread's ID */
    int t = 2024; /* data passed to the new thread */

    /* create a new thread that will execute 'PrintHello' */
    rc = pthread_create(&thread_id, NULL, PrintHello, (void*)t);
    
    if (rc) { /* could not create thread */
        printf("\n ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }

    printf("\n Created new thread (%lu) ...\n", thread_id);
    
    /* Main thread sleeps for 2 seconds */
    sleep(2);
    
    printf("\n Main thread finishing execution\n");

    /* Call pthread_exit() to prevent the main thread from terminating prematurely */
    pthread_exit(NULL);

    return 0;  // This will not be reached when pthread_exit() is called
}
