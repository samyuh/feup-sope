// PROGRAMA p02a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigterm_handler(int signo) {
  printf("Entering SIGTERM handler ...\n");
  sleep(10);
  printf("Exiting SIGTERM handler ...\n");
}

void sigint_handler(int signo) {
  printf("Entering SIGINT handler ...\n");
  sleep(10);
  printf("Exiting SIGINT handler ...\n");
}

int main(void) {
  struct sigaction actionOne, actionTwo;

  actionOne.sa_handler = sigint_handler;
  sigemptyset(&actionOne.sa_mask);
  actionOne.sa_flags = 0;

  actionTwo.sa_handler = sigterm_handler;
  sigemptyset(&actionTwo.sa_mask);
  actionTwo.sa_flags = 0;


  if (sigaction(SIGINT, &actionOne, NULL) < 0) {
    fprintf(stderr,"Unable to install SIGINT handler\n");
    exit(1);
  }
  else if (sigaction(SIGTERM, &actionTwo, NULL) < 0) {
    fprintf(stderr,"Unable to install SIGTERM handler\n");
    exit(2);
  }

  printf("Try me with CTRL-C ...\n");

  while(1) {
    pause();
  }
  exit(0);
}
