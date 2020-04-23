#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

struct num {
    int num1;
    int num2;
};

int main() {
   
    int filedes[2];
    pid_t pid;

    pipe(filedes);

    pid = fork();
    struct num number;
    if (pid == -1) {
        printf("Error on fork");
    }
    else if (pid == 0) { // child
        close(filedes[WRITE]);
        
        read(filedes[READ], &number, sizeof(struct num));
        printf("%d - %d = %d", number.num1, number.num2, number.num1-number.num2);
        
        close(filedes[READ]);
    }
    else { // parent
        close(filedes[READ]);

        scanf("%d %d", &number.num1, &number.num2);
        write(filedes[WRITE], &number, sizeof(struct num));

        close(filedes[WRITE]);
    }

}