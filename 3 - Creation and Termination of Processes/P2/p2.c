#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
	printf("1\n");
	if(fork() > 0) {
		printf("2");
		printf("3");
	} else {
		printf("4");
		printf("5");
	}
	printf("\n");
	return 0;
} 
