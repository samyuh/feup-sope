#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int readline(int fd, char *str);

int main(void){
    int fdr, fda, messagelen;
    int n[2];
    char str[100];
    char message[100];

    mkfifo("/tmp/fifo_ans", 0660);
    fda = open("/tmp/fifo_ans", O_WRONLY);
    
    mkfifo("/tmp/fifo_req", 0660);
    fdr = open("/tmp/fifo_req", O_RDONLY);

    while(readline(fdr, str)) {
        printf("%s", str);
        sscanf(str, "%d %d", &n[0], &n[1]);
        int sum = n[0] + n[1];
        sprintf(message,"%d\n", sum);
        messagelen = strlen(message) + 1;
        write(fda, message, messagelen);
    }
    close(fdr);
    close(fda);

    unlink("/tmp/fifo_req");
    unlink("/tmp/fifo_ans");
    return 0;
}

int readline(int fd, char *str) {
    int n;
    do {
        n = read(fd,str,1);
    } while (n>0 && *str++ != '\0');
    return (n>0);
} 