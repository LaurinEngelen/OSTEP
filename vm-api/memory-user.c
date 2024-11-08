#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <memory_in_MB> <time_in_seconds>\n", argv[0]);
        return 1;
    }

    printf("pid:%d\n", (int) getpid());
    int memory_mb = atoi(argv[1]);
    int time_seconds = atoi(argv[2]);

    // Calculate the number of bytes needed
    size_t memory_bytes = memory_mb * 1024 * 1024;

    // Allocate the array
    int *array = malloc(memory_bytes);
    if (array == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return 1;
    }

    // Get the starting time
    time_t start_time = time(NULL);

    // Stream through the array indefinitely or until the specified time
    while (1) {
        for (int i = 0; i < memory_bytes / sizeof(int); i++) {
            array[i] = i; // Touch the entry
        }

        // Check if the specified time has elapsed
        time_t current_time = time(NULL);
        if (difftime(current_time, start_time) >= time_seconds) {
            break;
        }
    }

    // Free the allocated memory
    free(array);

    return 0;
}
/*

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Kein Argument übergeben\n");
        return 1;
    }

    int megabyte = 1024 * 1024;
    int memory = atoi(argv[1]);
    int duration = 0; // Initialize duration to 0

    if (memory <= 0) {
        printf("Falsche Argumente übergeben\n");
        return 1;
    }

    if (argc == 3) {
        duration = atoi(argv[2]);
        if (duration <= 0) {
            printf("Falsche Argumente übergeben\n");
            return 1;
        }
    }

    int *Array = (int*)malloc(memory * megabyte / sizeof(int));
    if (Array == NULL) {
        printf("Speicherzuweisung fehlgeschlagen!\n");
        return 1;
    }

    if (argc == 2) {
        while (1) {
            for (int i = 0; i < memory * megabyte; i++) {
                Array[i] += 1;
            }
        }
    } else if (argc == 3) {
        time_t start_time = time(NULL);
        while (time(NULL) - start_time < duration) {
            for (int i = 0; i < memory * megabyte; i++) {
                Array[i] += 1;
            }
        }
    }

    free(Array);
    return 0;
}

*/