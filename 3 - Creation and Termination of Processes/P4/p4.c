#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	pid_t pid;
	pid = fork();
	if (pid == 0) { // child
		printf("Hello ");
	}
	else {
		printf("world!"); // parent 
	}
	exit(0);
}
