#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MAX 50000

int main(void) {
	pid_t pid;
	for (int i = 0; i < 3; i ++) {
		pid = fork();
		if (pid == 0) {
		    switch(i) {
		        case 0:
		            write(STDOUT_FILENO,"Hello ", 6);
		            break;
		        case 1:
		            write(STDOUT_FILENO,"my ", 3);
		            break;
		        case 2:
		            write(STDOUT_FILENO,"friends!\n", 11);
		            break;
		        default:
		            break;
		    }
		    break;
		}
	}
	return 0;
}
