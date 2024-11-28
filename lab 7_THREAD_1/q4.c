#include <stdio.h>
#include <pthread.h>

// Global account balance
int account = 1000;

// Mutex and condition variable to synchronize access to the account
pthread_mutex_t lock;
pthread_cond_t cond;

// Deposit function that adds an amount to the account
int deposit(int amount) {
    pthread_mutex_lock(&lock);  // Lock the mutex to ensure exclusive access

    account += amount;  // Add the deposit to the account
    printf("Deposited %d, Current balance: %d\n", amount, account);

    // If the balance is now greater than or equal to 1000, signal the withdrawal thread
    if (account >= 1000) {
        pthread_cond_signal(&cond);  // Wake up the withdrawal thread
    }

    pthread_mutex_unlock(&lock);  // Unlock the mutex after modifying the account
    return account;
}

// Withdrawal function that subtracts an amount from the account
int withdrawal(int amount) {
    pthread_mutex_lock(&lock);  // Lock the mutex to ensure exclusive access

    // Wait until the balance is >= 1000
    while (account < 1000) {
        printf("Waiting for balance to be at least 1000 to withdraw...\n");
        pthread_cond_wait(&cond, &lock);  // Block until signaled by the deposit function
    }

    account -= amount;  // Subtract the withdrawal amount from the account
    printf("Withdrew %d, Current balance: %d\n", amount, account);

    pthread_mutex_unlock(&lock);  // Unlock the mutex after modifying the account
    return account;
}

// Thread function for depositing money
void* depositThread(void* arg) {
    for (int i = 0; i < 20; i++) {  // Simulate multiple deposits
        deposit(500);  // Deposit 500
    }
    return NULL;
}

// Thread function for withdrawing money
void* withdrawThread(void* arg) {
    for (int i = 0; i < 30; i++) {  // Simulate multiple withdrawals
        withdrawal(300);  // Withdraw 300
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize the mutex and condition variable
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    // Create deposit and withdraw threads
    pthread_create(&t2, NULL, withdrawThread, NULL);
    pthread_create(&t1, NULL, depositThread, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy the mutex and condition variable
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    // Print final balance
    printf("Final balance: %d\n", account);

    return 0;
}
