#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	pid_t pid;
	pid = fork();
	if (pid > 0) { // parent
		sleep(1);
		printf(" world!");
	}
	else {
		printf("Hello"); // child 
	}
	exit(0);
}
