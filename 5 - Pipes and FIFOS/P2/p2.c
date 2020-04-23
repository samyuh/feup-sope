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
        
        int n[2];
        read(filedes[READ], &n, 2 * sizeof(int));
        close(filedes[READ]); // child: close read-descriptor

        int status = 0;
        int sum = n[0] + n[1];
        write(filedes[WRITE], &status, sizeof(int));
        write(filedes[WRITE], &sum, sizeof(int)); // child: reading only, so close write-descriptor.
        close(filedes[WRITE]);
    }
    else {
               int n[2];
        scanf("%d %d", &n[0], &n[1]);
        write(filedes[WRITE], &n, 2 * sizeof(int));
        close(filedes[WRITE]); // parent: close write-descriptor

        int status, sum;
        read(filedes[READ], &status, sizeof(int));
        if(status == 0) {
            read(filedes[READ], &sum, sizeof(int));
            printf("Sum = %d\n", sum);
        }
        close(filedes[READ]);
        
    }
    return 0;
}