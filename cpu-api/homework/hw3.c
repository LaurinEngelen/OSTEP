#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello (pid:%d)\n", (int) getpid());
    } else { // parent goes down this path (main)
        printf("goodbye (pid:%d)\n", (int) getpid());
    }
    return 0;
}

// Musterlösung mit Pipe, weil pipe die zwei Prozesse miteinader verbindet und das Lesende Ende erst ausgeführt wird, sobald es ein Signal vom schreibenden Teil gibt

