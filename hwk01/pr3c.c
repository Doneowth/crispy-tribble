#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
// Dong Liang
// 002128806

// zombie process, child done, parent never done
int
main(int argc, char *argv[])
{
    int rc = fork();
    
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc > 0) {
        while (1) {
            sleep(2);
            printf("%d parent alive...", (int)getpid());
        }
    } else if (rc == 0) {
        printf("%d child done!!! \n", (int)getpid());
    }
    
    return 0;
}
