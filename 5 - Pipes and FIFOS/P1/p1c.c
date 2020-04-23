#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main() {
    int filedes[2];
    pid_t pid;

    pipe(filedes);

    pid = fork();

    if (pid == -1) {
        exit(1);
    }
    else if (pid == 0) {
        close(filedes[WRITE]); // child: reading only, so close write-descriptor.
        char a[256];
        char b[256];
        read(filedes[READ], a, 256);
        read(filedes[READ], b, 256);
        int n[2];
        n[0] = atoi(a);
        n[1] = atoi(b);

        printf("Sum = %d\n", n[0] + n[1]);
        close(filedes[READ]); // child: close read-descriptor
    }
    else {
        close(filedes[READ]); // parent: writing only, so close read-descriptor.

        char a[256];
        char b[256];
        scanf("%s %s", a, b);
        write(filedes[WRITE], a, 256);
        write(filedes[WRITE], b, 256);

        close(filedes[WRITE]); // parent: close write-descriptor
    }


    return 0;
}