#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef enum {
    operation_sum = 0,
    operation_sub = 1,
    operation_mul = 2,
    operation_div = 3
} operation_t;

typedef struct {
    operation_t op;
    double a, b;
    pid_t pid;
} request_t;

void *th_operation(void *arg) {
    request_t *req = arg;
    double ans;
    switch(req->op){
        case operation_sum: 
            ans = req->a + req->b; 
            break;
        case operation_sub: 
            ans = req->a - req->b; 
            break;
        case operation_mul: 
            ans = req->a * req->b; 
            break;
        case operation_div: 
            ans = req->a / req->b; 
            break;
        default: 
            ans = 0; 
            break;
    }

    char buf[1024];
    sprintf(buf, "/tmp/fifo_ans_%d", req->pid);
    int ans_fifo = open(buf, O_WRONLY);
    write(ans_fifo, &ans, sizeof(double));
    return NULL;
}

int main(){
    mkfifo("/tmp/fifo_req", 0660);
    int req_fifo = open("/tmp/fifo_req", O_RDONLY);

    request_t *req = malloc(sizeof(request_t));
    pthread_t tid;
    int r;
    while((r = read(req_fifo, req, sizeof(request_t))) != -1) {
        if(req->a == 0 && req->b == 0) 
            break;
        pthread_create(&tid, NULL, th_operation, req);
    }
    free(req);
    close(req_fifo);
    unlink("/tmp/fifo_req");
    return 0;
}

int readline(int fd, char *str) {
    int n;
    do {
        n = read(fd,str,1);
    } while (n>0 && *str++ != '\0');
    return (n>0);
} 