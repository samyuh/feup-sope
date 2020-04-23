#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define WRITE 1
#define READ 0


int main(int argc, char * argv[]) {

    if (argc != 3) {
        exit(1);
    }

    int fd1[2];
    int fd2[2];
    pid_t pid;

    pipe(fd1);
    pipe(fd2);

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0) {
       /* Childs */
        close(fd1[WRITE]);
        pid = fork();

        if (pid == -1) {
            perror("fork2");
            exit(1);
        }
        else if (pid == 0) {
            close(fd2[WRITE]);
            close(fd1[READ]);

            // fd2 -> Input
            dup2(fd2[READ], STDIN_FILENO);
            close(fd2[READ]);
            execlp("sort", "sort", NULL); // 3º
        }
        else {
            close(fd2[READ]);

            //fd1 -> Input
            dup2(fd1[READ], STDIN_FILENO);

            // fd2 -> Output
            dup2(fd2[WRITE], STDOUT_FILENO);
            close(fd2[WRITE]);
            close(fd1[READ]);

            execlp("grep", "grep", argv[2], NULL); // 2º
        }
    }

    else {
         /* Parent */ 
        close(fd1[READ]);
        close(fd2[READ]);
        close(fd2[WRITE]);

        // fd1 -> Standart output
        dup2(fd1[WRITE], STDOUT_FILENO);
        close(fd1[WRITE]);

        execlp("ls", "ls", argv[1], "-laR", NULL); // 1º
    }

    return 0;
}