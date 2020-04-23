#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main(int argc, char * argv[]) {
    if (argc != 2) 
        return 1;

    FILE * file;

    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error on fork");
        exit(1);
    }
    else if (pid == 0) {
        close(fd[WRITE]);
        dup2(fd[READ], STDIN_FILENO);
        close(fd[READ]);

        execlp("sort", "sort", NULL);
    }
    else {
        close(fd[READ]);

        file = fopen(argv[1], "r");

        char c[2];
        while(fgets(c, 2, file) != NULL)
            write(fd[WRITE], c, 1);


        close(fd[WRITE]);
    }

    fclose(file);
    return 0;
}