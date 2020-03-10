// PROGRAMA p5b.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
  int fd;
  char *text1="CCCCC";
  char *text2="DDDDD";

  fd = open("f1.txt", O_WRONLY|O_SYNC,0600);
  write(fd,text1,5);
  write(fd,text2,5);
  close(fd);
  return 0;
}

