#include <stdio.h>
#include <pthread.h>

// Function that the new thread will execute
void* PrintHello(void* arg) {
    pthread_t main_thread_id = *(pthread_t*)arg;  // Get the main thread's ID
    pthread_t current_thread_id = pthread_self(); // Get the current thread's ID

    // Print thread IDs
    printf("\nHello from the new thread!\n");
    printf("Main thread ID passed into new thread: %lu\n", main_thread_id);
    printf("Current thread (new thread) ID: %lu\n\n", current_thread_id);

    return NULL;
}

int main() {
    pthread_t main_thread_id, new_thread_id; // Declare thread IDs

    // Get the main thread's ID
    main_thread_id = pthread_self();
    printf("Main thread ID: %lu\n", main_thread_id);

    // Create a new thread, passing the main thread's ID as an argument
    if (pthread_create(&new_thread_id, NULL, PrintHello, (void*)&main_thread_id)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // Wait for the new thread to finish
    if (pthread_join(new_thread_id, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    printf("Main thread finishing execution\n");
    return 0;
}
