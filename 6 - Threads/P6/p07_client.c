#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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

int main(int argc, char *argv[]){
    if(argc != 4) return EXIT_FAILURE;

    request_t req;

    if (strcmp(argv[1], "sum") == 0) 
        req.op = operation_sum;
    else if(strcmp(argv[1], "sub") == 0)
        req.op = operation_sub;
    else if(strcmp(argv[1], "mul") == 0) 
        req.op = operation_mul;
    else if(strcmp(argv[1], "div") == 0) 
        req.op = operation_div;
    else return EXIT_FAILURE;

    sscanf(argv[2], "%lf", &req.a);
    sscanf(argv[3], "%lf", &req.b);

    req.pid = getpid();
    
    int req_fifo = open("/tmp/fifo_req", O_WRONLY);
    write(req_fifo, &req, sizeof(request_t));
    close(req_fifo);

    if(req.a == 0 && req.b == 0) return 0;

    char ans_fifo_path[1024];
    sprintf(ans_fifo_path, "/tmp/fifo_ans_%d", req.pid);
    mkfifo(ans_fifo_path, 0660);
    int ans_fifo = open(ans_fifo_path, O_RDONLY);

    double ans;
    read(ans_fifo, &ans, sizeof(double));
    close(ans_fifo);
    unlink(ans_fifo_path);

    printf("%lf\n", ans);
    
    return 0;
}