#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
// Dong Liang
// 002128806
int
main(int argc, char *argv[])
{
    char str[1024];

    int rc = fork();
    
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("Enter a number: ");
        if (fgets(str, sizeof str, stdin))
            str[strcspn(str, "\n")] = '\0';
        // printf("%d", atoi(str));
        exit(atoi(str));
    } else {
        int status_code;
        wait(&status_code);
        const int es = WEXITSTATUS(status_code);
        printf("child exited with status %d \n", es);
    }
    
    return 0;
}
