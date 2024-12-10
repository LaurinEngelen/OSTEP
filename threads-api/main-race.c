#include <stdio.h>

#include "common_threads.h"

int balance = 0;

void* worker(void* arg) {
    pthread_mutex_t lock2;
    int rc = pthread_mutex_init(&lock2, NULL);
    assert(rc == 0);
    pthread_mutex_lock(&lock2);
    balance = 1; // unprotected access
    printf("balance = %d\n", balance);
    pthread_mutex_unlock(&lock2); 
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_mutex_t lock1;
    int rc = pthread_mutex_init(&lock1, NULL);
    assert(rc == 0);
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    Pthread_join(p, NULL);
    pthread_mutex_lock(&lock1);
    balance = 2; // unprotected access
    printf("balance = %d\n", balance);
    pthread_mutex_unlock(&lock1);
    return 0;
}
