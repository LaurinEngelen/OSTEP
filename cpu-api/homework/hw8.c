#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    // Deklaration von Variablen
    int fd[2], nbytes;
    pid_t pid1, pid2;
    char readbuffer[80];

    // Erstellen einer Pipe
    pipe(fd);

    // Forken eines neuen Prozesses
 pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) {
        // Schließen des Schreibenden Ende der Pipe
        close(fd[1]);
        // Lesen aus der Pipe
        dup2(fd[0], STDIN_FILENO); // nimmt stdin von der Pipe
        read(fd[0], readbuffer, sizeof(readbuffer));
        printf("Erhaltener string: %s", readbuffer);
        exit(0);
    }

    // Zweiter Kindprozess erstellen
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    } else if (pid2 == 0) {
        // Schließen des Lesenden Ende der Pipe
        close(fd[0]);
        // Schreiben in die Pipe
        dup2(fd[1], STDOUT_FILENO); // Leite stdout auf die Pipe um
        printf("Nachricht vom Zweiten Kind!\n");
        exit(0);
    }

        // Elternprozess
        // Warten auf den Kindprozess
        wait(NULL);
    

    return 0;
}