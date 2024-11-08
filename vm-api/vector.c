#include <stdio.h>
#include <stdlib.h>

typedef struct vector {
        int *start;
        int size;
} vector;

void add(vector *v, int data) {
    v->size = v->size + 1;
    v->start = realloc(v->start, v->size * sizeof(int));
    v->start[v->size - 1] = data;
}

void free_vector(vector *v) {
    free(v->start);
    free(v);
}

vector *create_vector(int data) {
    vector *v = malloc(sizeof(vector));
    v->start = malloc(sizeof(int));
    v->start[0] = data;
    v->size = 1;
    return v;
}

int main(int argc, char **argv) {
    vector *v = create_vector(1);

    add(v, 2);
    add(v, 3);
    add(v, 5);

    for (int i = 0; i < v->size; i++) {
        printf("%d\n", v->start[i]);
    }

    free_vector(v);
    return 0;
}