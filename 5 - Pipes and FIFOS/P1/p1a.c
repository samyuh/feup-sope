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

        int n[2];
        read(filedes[READ], n, 2 * sizeof(int));
        printf("Sum = %d\n", n[0] + n[1]);
        printf("Dif = %d\n", n[0] - n[1]);
        printf("Product = %d\n", n[0] * n[1]);
        if (n[1] == 0)
            printf("Div = invalid");
        else
            printf("Div = %lf\n", n[0]/n[1]);

        close(filedes[READ]); // child: close read-descriptor
    }
    else {
        close(filedes[READ]); // parent: writing only, so close read-descriptor.

        int n[2];
        scanf("%d %d", &n[0], &n[1]);
        write(filedes[WRITE], n, 2 * sizeof(int));

        close(filedes[WRITE]); // parent: close write-descriptor
    }


    return 0;
}
