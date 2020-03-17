#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo) {
   printf("In SIGINT handler ...\n");
}

int main(void) {
  struct sigaction sigAct;

  sigAct.sa_handler = sigint_handler;
  sigemptyset(&sigAct.sa_mask);
  sigAct.sa_flags = 0;

  int time = 30;
  if (sigaction(SIGINT, &sigAct, NULL) < 0) {
   fprintf(stderr,"Unable to install SIGINT handler\n");
   exit(1);
  }
  printf("Sleeping for 30 seconds ...\n");
  while(time != 0) {
      time = sleep(time);
  }
  printf("Waking up ...\n");
  exit(0);
}
