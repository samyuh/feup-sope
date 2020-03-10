// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUF_LENGTH 256

int main(int argc, char *argv[]) {
    int fd1, fd2, nr;
    char buf[BUF_LENGTH];
    if (argc != 3){
        printf("usage: %s file1 file2\n", argv[0]);
        exit(errno);
    }

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("ERROR");
        printf("%s", strerror(errno));
        printf("%d\n", errno);
        exit(1);
    }

    fd2 = open(argv[2], O_WRONLY);
    if (fd2 == -1) {
        perror("ERROR");
        printf("%s", strerror(errno));
        printf("%d\n", errno);
        exit(2);
    }
    while (nr = read(fd1, buf, BUF_LENGTH) > 0) {
	write(fd2, buf, nr);
    }
    close(fd1);
    close(fd2);
    exit(0);
} 
