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
        //hier execls rein


    } else { // parent goes down this path (main)
        printf("goodbye (pid:%d)\n", (int) getpid());
    }
    return 0;
}

/*
execl(): Nimmt eine Liste von Argumenten entgegen.
        execl("/bin/ls", "ls", "-l", "-a", (char*)NULL);

execle(): Ähnlich wie execl(), aber mit zusätzlichen Umgebungsvariablen.
        

execlp(): Nimmt eine Liste mit Argumenten, die ein Nullpointer terminiert.
        execlp("ls", "ls", "-l", NULL);

execv(): Nimmt ein Array von Argumenten entgegen. 
        
execvp(): Ähnlich wie execv(), aber sucht nach dem Programm in einem angegebenen Pfad.
        char *myargs[3];
        myargs[0] = strdup("/bin/ls");
        myargs[1] = strdup("ls");
        myargs[4] = NULL;          // marks end of array
        execvp(myargs[0], myargs); 

        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        
execvpe(): Nimmt ein Array von Zeigern auf nullterminierte Zeichenketten
        


DESCRIPTION
       The  exec()  family  of  functions replaces the current process image with a new process image.  The functions described in this manual page are layered on top of ex-
       ecve(2).  (See the manual page for execve(2) for further details about the replacement of the current process image.)

       The initial argument for these functions is the name of a file that is to be executed.

       The functions can be grouped based on the letters following the "exec" prefix.

   l - execl(), execlp(), execle()
       The const char *arg and subsequent ellipses can be thought of as arg0, arg1, ..., argn.  Together they describe a list of one  or  more  pointers  to  null-terminated
       strings  that represent the argument list available to the executed program.  The first argument, by convention, should point to the filename associated with the file
       being executed.  The list of arguments must be terminated by a null pointer, and, since these are variadic functions, this pointer must be cast (char *) NULL.

       By contrast with the 'l' functions, the 'v' functions (below) specify the command-line arguments of the executed program as a vector.

   v - execv(), execvp(), execvpe()
       The char *const argv[] argument is an array of pointers to null-terminated strings that represent the argument list available to the new program.  The first argument,
       by convention, should point to the filename associated with the file being executed.  The array of pointers must be terminated by a null pointer.

   e - execle(), execvpe()
       The  environment  of  the caller is specified via the argument envp.  The envp argument is an array of pointers to null-terminated strings and must be terminated by a
       null pointer.

       All other exec() functions (which do not include 'e' in the suffix) take the environment for the new process image from the external variable environ in  the  calling
       process.

   p - execlp(), execvp(), execvpe()
       These  functions duplicate the actions of the shell in searching for an executable file if the specified filename does not contain a slash (/) character.  The file is
       sought in the colon-separated list of directory pathnames specified in the PATH environment variable.  If this variable isn't defined, the path  list  defaults  to  a
       list  that includes the directories returned by confstr(_CS_PATH) (which typically returns the value "/bin:/usr/bin") and possibly also the current working directory;
       see NOTES for further details.


*/