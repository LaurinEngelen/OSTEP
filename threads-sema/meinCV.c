#include <stdio.h>
#include <unistd.h>
#include "common_threads.h"

pthread_cond_t c1;
pthread_mutex_t l1;
pthread_t t1, t2;
int count = 0;


void* func1() {
    Pthread_mutex_lock(&l1);
        count = 1;
        printf("Funktion1\n");
        Pthread_cond_signal(&c1);
    Pthread_mutex_unlock(&l1);
    return NULL; 
}

void* func2() {
    Pthread_mutex_lock(&l1);
    while (count == 0){
        Pthread_cond_wait(&c1, &l1);
    };  
    printf("Funktion2\n");
    Pthread_mutex_unlock(&l1);
    return NULL;
}

int main(int argc, char const *argv[])
{
    Pthread_mutex_init(&l1, 0);
    Pthread_cond_init(&c1, 0);
    Pthread_create(&t1, NULL, *func1, NULL);
    Pthread_create(&t2, NULL, *func2, NULL);

    Pthread_join(t1, 0);
    Pthread_join(t2, 0);
}
