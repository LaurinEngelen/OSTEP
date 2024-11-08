#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int rc = fork();

    if (rc < 0) {
        // Fehler beim Forken
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Kindprozess

        // Umleitung der Standardausgabe in eine Datei
        close(STDOUT_FILENO);  // Schließe den aktuellen STDOUT-Filedescriptor
        printf("hallo von kind");

    } else {
        // Elternprozess
        int rcwait = wait(NULL);  // Warte auf die Beendigung des Kindes
    }

    return 0;
}

// => Nach dem schließen vom Descriptor, gibt es kein Output mehr