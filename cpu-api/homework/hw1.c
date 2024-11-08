#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int x = 100;
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    int rb = fork();
    int rd = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0 || rb == 0 || rd == 0) { // child (new process)
        x = x - 10;
        printf("hello, I am child (pid:%d) and x:%d\n", (int) getpid(),x);
    } else { // parent goes down this path (main)
        int rc_wait = wait(NULL);
        x = x - 20;
        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d) and x:%d\n",
               rc, rc_wait, (int) getpid(), x);
    }
    return 0;
}

// => es wird eine Kopie von x erstellt und jeder Prozess und Childprozess hat sein eigenes x

/*Output:

hello world (pid:2817)
hello, I am child (pid:2818) and x:90
hello, I am parent of 2818 (rc_wait:2818) (pid:2817) and x:80

*/