// PROGRAMA p1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int global=1;
int main(void) {
 int local = 2;
 if(fork() > 0) {
 printf("PID = %d; PPID = %d\n", getpid(), getppid());
 global++;
 local--;
 } else {
 printf("PID = %d; PPID = %d\n", getpid(), getppid());
 global--;
 local++;
 }
 printf("PID = %d - global = %d ; local = %d\n", getpid(), global, local);
 return 0;
} 
