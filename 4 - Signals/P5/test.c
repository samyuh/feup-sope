#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[], char * envp[]) {
  char *fd1;
  if(getenv("Path") != NULL) { // If path variable is defined to write the log
	 printf("Escrever o log");
  }
  else {
    printf("Not defined!\n");
  }
	return 0;
}
