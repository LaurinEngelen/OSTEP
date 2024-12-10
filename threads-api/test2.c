#include <stdio.h>
#include "common_threads.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t init = PTHREAD_COND_INITIALIZER; 
int initialized;

void* worker1 (void* arg) {
    pthread_mutex_lock(&lock); 
    initialized = 1; 
    printf("signal senden\n");
    pthread_cond_signal(&init); 
    pthread_mutex_unlock(&lock);
}

void* worker2 (void* arg) {
    printf("warte auf signal\n%d\n", initialized);
    pthread_mutex_lock(&lock); 
    while (initialized == 0)
        pthread_cond_wait(&init, &lock); 
    printf("signal empfangen\n"); 
    pthread_mutex_unlock(&lock);
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    Pthread_create(&p1, NULL, worker1, NULL);
    Pthread_create(&p2, NULL, worker2, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    return 0;
}