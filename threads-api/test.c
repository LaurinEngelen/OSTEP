#include <stdio.h>
#include "common_threads.h"

typedef struct __myargs {
    int a;
    int b;
} myargs;

int worker (void* arg) {
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    myargs *m = (myargs*) arg;
    pthread_mutex_lock(&lock);
    m->a = 2 * (m->a);
    m->b = 2 * (m->b);
    pthread_mutex_unlock(&lock);
    printf("a= %d, b= %d\n", m->a, m->b);
    return 1;
}

int main(int argc, char *argv[]) {
    int rc1;
    int rc2;
    pthread_t p1, p2;
    myargs arg1, arg2;
    arg1.a = 1;
    arg1.b = 2;

    arg2.a = 3;
    arg2.b = 4;

    pthread_create(&p1, NULL, worker, &arg1);
    pthread_create(&p2, NULL, worker, &arg2);
    pthread_join(p1, (void *)rc1);
    pthread_join(p2, (void *)rc2);

    printf("rc1 = %d, rc2 = %d\n", rc1, rc2);
}