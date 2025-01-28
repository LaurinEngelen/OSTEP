#include <stdio.h>
#include <unistd.h>
#include "common_threads.h"

sem_t c1, c2, lock;
pthread_t t1, t2, t3, t4;

void *partner1() {
    sem_post(&c2);
    sem_wait(&c1);
    printf("partner1 läuft\n");
}

void *partner2() {
    sem_post(&c1);
    sem_wait(&c2);
    printf("partner2 läuft\n");
}

int main() {
    sem_init(&c1, 0, 0);
    sem_init(&c2, 0, 0);
    sem_init(&lock, 0,1);
    Pthread_create(&t1, 0, partner1, 0);
    Pthread_create(&t2, 0, partner2, 0);
    Pthread_create(&t3, 0, partner1, 0);
    Pthread_create(&t4, 0, partner2, 0);

    Pthread_join(t1, 0);
    Pthread_join(t2, 0);
    Pthread_join(t3, 0);
    Pthread_join(t4, 0);

}