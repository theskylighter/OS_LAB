#include <stdio.h>
#include <pthread.h>

int balance = 1000;  // Global variable for balance
pthread_mutex_t lock;  // Mutex to prevent interleaving

// Thread function to deposit an amount 50 times
void* deposit(void* arg) {
    for (int i = 0; i < 50; i++) {

        // Lock the mutex before modifying the balance
        pthread_mutex_lock(&lock);
        
        balance += 50;  // Deposit 50
        printf("Deposited 50, Current balance: %d\n", balance);

        // Unlock the mutex after modifying the balance
        pthread_mutex_unlock(&lock);
        
    }
    return NULL;
}

// Thread function to withdraw an amount 20 times
void* withdraw(void* arg) {
    for (int i = 0; i < 20; i++) {
        // Lock the mutex before modifying the balance
        pthread_mutex_lock(&lock);
        
        if (balance >= 20) {
            balance -= 20;  // Withdraw 20
            printf("Withdrew 20, Current balance: %d\n", balance);
        } else {
            printf("Not enough balance to withdraw.\n");
        }

        // Unlock the mutex after modifying the balance
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create threads
    pthread_create(&t1, NULL, deposit, NULL);
    pthread_create(&t2, NULL, withdraw, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    // Print the final balance
    printf("Final balance: %d\n", balance);

    return 0;
}
