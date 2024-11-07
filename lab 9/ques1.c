#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_LEN 1000 

char *s1, *s2;     
int n1, n2;         
int totalMatches = 0; // Global count for matches
pthread_mutex_t lock; 


void *count_substrings(void *arg) {
    int start = *(int *)arg;
    int localMatches = 0;

    for (int i = start; i <= start + n1 / 2 - n2; i++) {
        if (strncmp(s1 + i, s2, n2) == 0) {
            localMatches++;
        }
    }

    // Locking for thread-safe increment
    pthread_mutex_lock(&lock);
    totalMatches += localMatches;
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    FILE *file = fopen("strings.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Allocate memory for s1 and s2 and initialize to zero
    s1 = malloc(MAX_LEN);
    s2 = malloc(MAX_LEN);

    // Read s1 and s2 from the file
    fscanf(file, "s1: %[^\n]\ns2: %[^\n]", s1, s2);
    fclose(file);

    // Get lengths of s1 and s2
    n1 = strlen(s1);
    n2 = strlen(s2);

    // Check that the problem constraints are satisfied
    if (n1 % 2 != 0 || n2 > n1 / 2) {
        printf("Input constraints not satisfied.\n");
        return 1;
    }

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    pthread_t threads[2];
    int startIndices[2] = {0, n1 / 2};

    // Create two threads to search each half of s1
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, count_substrings, &startIndices[i]);
    }

    // Wait for both threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    // Print the total number of matches found
    printf("Total number of matched substrings: %d\n", totalMatches);

    // Free allocated memory
    free(s1);
    free(s2);

    return 0;
}