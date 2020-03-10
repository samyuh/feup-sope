// PROGRAMA p6b.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUF_LENGTH 256

int main(int argc, char *argv[]) {
    int file1 = open(argv[1], O_RDONLY);
    int file2;
    if (argc != 2 && argc != 3) {
        printf("usage: %s file1 [file2]\n", argv[0]);
        exit(0);
    }

    if (file1 == -1) {
        perror(argv[1]);
        exit(2);
    }
    if (argc == 3) {
        file2 = open(argv[2], O_WRONLY | O_EXCL | O_CREAT, 0644);
        if (file2 == -1) {
            perror(argv[2]);
            close(file1);
            exit(2);
        }
        dup2(file2, STDOUT_FILENO);
    }
    
    char buffer[BUF_LENGTH];
    int read_chars;
    while ( (read_chars = read(file1, buffer, BUF_LENGTH)) > 0) {
        write(STDOUT_FILENO, buffer, read_chars);
    }
    close(file1);

    if (argc == 3) close(file2);
    exit(0);
}
