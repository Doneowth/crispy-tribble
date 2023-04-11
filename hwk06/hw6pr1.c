#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#define ITER_NUM 2
#define FATHER "hello father\n"
#define CHILD "hello child\n"

// Dong Liang
// 002128806
void write_test();

int
main(int argc, char *argv[])
{
    int fd = open("test_txt.txt", O_RDWR);
    int i = 0;
    int rc = fork();
    
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        while(i < ITER_NUM) {
            sleep(1);
            write_test(fd, CHILD);
            i++;
        }

        printf("%d child done!!! \n", (int)getpid());
    } else {
        while(i < ITER_NUM) {
            sleep(1);
            write_test(fd, FATHER);
            i++;
        }
        printf("%d parent done!!! \n", (int)getpid());
    }
    
    return EXIT_SUCCESS;
}


void
write_test(int fd, char *str)
{
    char *ptr;
    int c;
    for(ptr=str;(c=*ptr++)!= 0;)
        write(fd, &c, 1);
}