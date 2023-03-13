#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

int
main(int argc, char **argv)
{   
    int pid = fork();
    if (pid < 0) {
        exit();
    }
    else if (pid > 0) {
        ps();
    } 
    else {
        printf(1, "this is child process from PS, TEST ONLY \n");
    }
    wait();
    exit();
}