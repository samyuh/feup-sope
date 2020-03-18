#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int inc = 1;

void handler(int signo) {
  if(signo == SIGUSR1) {
    inc = 1;
  }
  else if (signo == SIGUSR2) {
        inc = -1;
    }
}

int main() {
  int v = 0;

  struct sigaction actionOne;

  actionOne.sa_handler = handler;
  sigemptyset(&actionOne.sa_mask);
  actionOne.sa_flags = 0;

  if (sigaction(SIGUSR1, &actionOne, NULL) < 0) {
    fprintf(stderr,"Unable to install SIGUSR1 handler\n");
    exit(1);
  }
  else if (sigaction(SIGUSR2, &actionOne, NULL) < 0) {
    fprintf(stderr,"Unable to install SIGUSR2 handler\n");
    exit(2);
  }

  pid_t pid = fork();

  if (pid == -1) {
      printf("ERROR");
      exit(1);
  }
  if (pid > 0) {
      while(1) {
          int random = rand() % 2;
          if(random == 0) {
            kill(pid, SIGUSR1);
          }
          else {
            kill(pid, SIGUSR2);
          }
          sleep(5);
      }
  }
  if (pid < 0) {
      int counter = 0;
      while(counter != 50) {
        v += inc;
        counter++;
        sleep(1);
        printf("%d\n", v);
      }
      kill(getppid(), SIGTERM); // matar o pai
      raise(SIGTERM); // cometer suicidio
  }
  exit(0);
}
