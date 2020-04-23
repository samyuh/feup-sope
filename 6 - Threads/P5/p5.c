
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 4


void * thr_sum(void * arg) {
    int n1 = ((int *) arg)[0];
    int n2 = ((int*) arg)[1];
    printf("%d + %d = %d\n", n1, n2, n1+n2);
    return NULL;
}
void * thr_dif(void * arg) {
    int n1 = ((int *) arg)[0];
    int n2 = ((int*) arg)[1];
    printf("%d - %d = %d\n", n1, n2, n1-n2);
    return NULL;
}
void * thr_mult(void * arg) {
    int n1 = ((int *) arg)[0];
    int n2 = ((int*) arg)[1];
    printf("%d * %d = %d\n", n1, n2, n1*n2);
    return NULL;
}
void * thr_quo(void * arg) {
    int n1 = ((int *) arg)[0];
    int n2 = ((int*) arg)[1];
    printf("%d / %d = %d\n", n1, n2, n1/n2);
    return NULL;
}

int main() {

    void *(*THREAD_FUNC[NUM_THREADS])(void*) = {
        thr_sum,
        thr_dif,
        thr_mult,
        thr_quo
    };

    pthread_t threads[NUM_THREADS];
    int iter[NUM_THREADS];
    int nums[2];

    scanf("%d", &nums[0]);
    scanf("%d", &nums[1]);
    
    
    for (int i = 0; i < NUM_THREADS; i++) {
        iter[i] = i;
        pthread_create(&threads[iter[i]], NULL, THREAD_FUNC[iter[i]], (void*)nums);
    }


    pthread_exit(0);
}