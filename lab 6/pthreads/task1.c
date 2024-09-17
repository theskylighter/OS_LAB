#include <stdio.h>   /* standard I/O routines */
#include <pthread.h> /* pthread functions and data structures */
#include <stdlib.h>  /* for exit() */
 
/* function to be executed by the new thread */
void* PrintHello(void* data) {
    int my_data = (int)data; /* safely cast the data received by thread */
    pthread_detach(pthread_self());    /* detach the thread */
    
    printf("Hello from new thread - got %d\n", my_data);
    
    pthread_exit(NULL); /* terminate the thread */
}

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[]) {
    int rc; /* return value */      
    pthread_t thread_id; /* thread's ID (just an integer) */
    int t = 2024; /* data passed to the new thread */
    
    /* create a new thread that will execute 'PrintHello' */
    rc = pthread_create(&thread_id, NULL, PrintHello, (void*)t);
    
    if (rc) { /* could not create thread */
        printf("\n ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
    
    printf("\n Created new thread (%lu) ... \n", thread_id);
    
    pthread_exit(NULL); /* terminate the thread */
}
