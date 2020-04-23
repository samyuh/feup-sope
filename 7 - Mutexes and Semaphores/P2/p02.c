// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR 2
#define NUMITER 10000

int N = 5000;

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; // mutex

void * thrfunc(void * arg) {
    void * i = malloc(sizeof(int));
    *(int*) i = 0;
    fprintf(stderr, "Starting thread %s\n", (char *) arg);
    while(1) {
        pthread_mutex_lock(&mut);
        if (N <= 0) {
            pthread_mutex_unlock(&mut);
            break;
        }
        write(STDERR,arg,1);
        N--;
        (*(int*) i)++;
        pthread_mutex_unlock(&mut);
    }
    return i;
}

int main() {
    pthread_t ta, tb;
    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");

    void * count1, * count2;
    pthread_join(ta, &count1);
    pthread_join(tb, &count2);

    fprintf(stderr, "\nThread 1 - %d\n", *((int *)count1));
    fprintf(stderr, "Thread 2 - %d\n", *((int *)count2));

    free(count1);
    free(count2);
    return 0;
} 