#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
// Dong Liang
// 002128806
// orphan process: parent done, but child never ends
int
main(int argc, char *argv[])
{
    int rc = fork();
    
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        while (1) {
            sleep(2);
            printf("%d child alive...", (int)getpid());
        }
    } else {
        printf("%d parent done!!! \n", (int)getpid());

    }
    
    return 0;
}
