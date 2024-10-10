#include <stdio.h>   /* standard I/O routines */
#include <pthread.h> /* pthread functions and data structures */
#include <stdlib.h>
#include<unistd.h>

/* function to be executed by the new thread */
void *PrintHello(void *data)
{
    int my_data = (int)data; /* data received by thread */
    // pthread_detach(pthread_self());

    sleep(2);

    printf("\nRunning thread id : %lu \n", pthread_self());
    printf("Hello from new thread - got %d\n", my_data);

    pthread_exit(NULL); /* terminate the thread */
}
    void *printThreadID(void *data)
    {
        pthread_t main_thread_id = *(pthread_t*)data;  // Get the main thread's ID
        pthread_t current_thread_id = pthread_self(); // Get the current thread's ID
        // pthread_detach(pthread_self());

        printf("\nMain thread id passed into thread : %lu \n", main_thread_id);
        printf("currently Running thread id : %lu \n", pthread_self());
       

        pthread_exit(NULL); /* terminate the thread */
    }


int main(int argc, char *argv[])
{
    pthread_t thread_id; 
    pthread_t thread_id2;
    int t = 2024;         
    
    pthread_t mainThreadID=pthread_self() ;
    printf("\nFrom main func, main thread id : %lu\n",mainThreadID);
    
    if (pthread_create(&thread_id2, NULL, printThreadID,&mainThreadID)) 
    {
        fprintf(stderr,"\n ERROR in creating thread \n");
        exit(1);
    }
    printf("\nCreated new thread (%lu) ... \n", thread_id2);
    if (pthread_join(thread_id2, NULL)) 
    {
        fprintf(stderr,"\n error joining thread 2\n");
        exit(1);
    }
    
    
    if (pthread_create(&thread_id, NULL, PrintHello, (void *)t)) 
    {
        printf("\n ERROR in creating thread \n");
        exit(1);
    }
    printf("\nCreated new thread (%lu) ... \n", thread_id);
    // if(pthread_join(thread_id,NULL)){
    //     printf("error joining thread 1\n");
    // }

    // pthread_exit(NULL); /* terminate the thread */
}