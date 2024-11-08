#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int *data = (int*) malloc(100 * sizeof(int));
    free(data);
    printf("Inhalt: %d\n",data[99]);
}