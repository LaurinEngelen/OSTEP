#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd = open("./test",O_CREAT| O_RDWR);
    if (fd == -1){
        perror("open");
        return -1;
    }
    printf("hello (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("child (pid:%d)\n", (int) getpid());
        write(fd, "Childprocess",12);
    } else { // parent goes down this path (main)
        printf("parent of %d (pid:%d)\n",
               rc, (int) getpid());
        write(fd, " Parentprocess", 14);
    }
    return 0;
}

// => beide können auf den file descriptor zugreifen und in die datei rein schreiben
//    die Prozesse schreiben nacheinadner