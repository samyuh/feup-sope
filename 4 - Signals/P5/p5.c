#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void sigchld_handler(int signo) {
   printf("In SIGCHLD handler...\n");
   wait(NULL); 
   printf("Exit SIGCHLD handler\n");
}

int main(void) {
  struct sigaction sigAct;

  sigAct.sa_handler = sigchld_handler;
  sigemptyset(&sigAct.sa_mask);
  sigAct.sa_flags = 0;

  if (sigaction(SIGCHLD, &sigAct, NULL) < 0) {
   fprintf(stderr,"Unable to install SIGCHLD handler\n");
   exit(1);
  }

  pid_t pid;
  int i, n;

  for (i=1; i<=3; i++) {
    pid=fork();
    if (pid == 0) {
      printf("CHILD no. %d (PID=%d) working ... \n",i , getpid());
      sleep(i*7); // child working ...
      printf("CHILD no. %d (PID=%d) exiting ... \n",i , getpid());
      exit(0);
    }
  }

  for (i=1; i<=4; i++) {
    printf("PARENT: working hard (task no. %d) ...\n", i);
    n = 20;
    while((n=sleep(n))!=0);
    printf("PARENT: end of task no. %d\n",i);
    printf("PARENT: waiting for child no. %d ...\n", i);
  }
  exit(0);
}
