#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int readline(int fd, char *str);

int main(void) {
    int fda, fdr, messagelen, i;
    int n[2];
    char message[100];

    do {
        fda = open("/tmp/fifo_ans", O_RDONLY);
        if (fda==-1) 
            sleep(1);
    } while (fda==-1);

    do {
        fdr = open("/tmp/fifo_req", O_WRONLY);
        if (fdr==-1) 
            sleep(1);
    } while (fdr==-1);

    do {
        scanf("%d %d", &n[0], &n[1]);
        sprintf(message,"%d %d\n", n[0], n[1]);
        messagelen = strlen(message) + 1;
        write(fdr, message, messagelen);
        printf("Sum: ");
        readline(fda, message);
        printf("%s", message);
    } while(n[0] != 0 && n[1] != 0);
    
    
    close(fdr);
    close(fda);
    return 0;
}

int readline(int fd, char *str) {
    int n;
    do {
        n = read(fd,str,1);
    } while (n>0 && *str++ != '\0');
    return (n>0);
} 
