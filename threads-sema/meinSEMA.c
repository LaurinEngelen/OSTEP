#include <stdio.h>
#include <unistd.h>
#include "common_threads.h"

sem_t s1, lock;
pthread_t t1, t2;


void* func1() {
    sem_wait(&lock);
        sem_post(&s1);
        printf("Funktion1\n");
    sem_post(&lock);
    return NULL; 
}

void* func2() {
    sem_wait(&lock);
        sem_wait(&s1);
        printf("Funktion2\n");
    sem_post(&lock);
    return NULL;
}

int main(int argc, char const *argv[])
{
    sem_init(&s1, 0, 0);
    sem_init(&lock, 0, 1);
    Pthread_create(&t1, NULL, *func1, NULL);
    Pthread_create(&t2, NULL, *func2, NULL);

    Pthread_join(t1, 0);
    Pthread_join(t2, 0);
}
