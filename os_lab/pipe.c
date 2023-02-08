// C program for passing value from
// child process to parent process
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#define MAX 10

int main()
{

    int fd[2], i = 0;
    pipe(fd);
    pid_t pid = fork();

    if(pid > 0) {
        wait(NULL);
        close(0);
        close(fd[1]);
        dup(fd[0]);
        char arr[10];
        int n = read(fd[0], arr, strlen(arr)+1);
        for ( i = 0;i < n; i++)
            printf("%c ", arr[i]);
    }
    else if( pid == 0 ) {
        char arr[1024] = "abcd";
        close(fd[0]);
        close(1);	
        dup(fd[1]);
        write(1, arr, strlen(arr)+1);
    }

}
