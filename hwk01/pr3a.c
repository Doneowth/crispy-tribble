#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
// Dong Liang
// 002128806
// int
// main(int argc, char *argv[])
// {
//     char str[1024];

//     int rc = fork();
    
//     if (rc < 0) {
//         // fork failed; exit
//         fprintf(stderr, "fork failed\n");
//         exit(1);
//     } else if (rc == 0) {
//         // child (new process)
//         printf("Enter a number: ");
//         if (fgets(str, sizeof str, stdin))
//             str[strcspn(str, "\n")] = '\0'; // TIP: swap \n with \0
//         // printf("%d", atoi(str));
//         exit(atoi(str));
//     } else {
//         int status_code;
//         wait(&status_code);
//         const int es = WEXITSTATUS(status_code);
//         printf("child exited with status %d \n", es);
//     }
    
//     return 0;
// }

// another way to solve this is to use a PIPE
int 
main() {

    int rc = fork();
    int c_p[2];
    int i = 0;
    int c2p = pipe(c_p);
    // child => parent
    // child write, parent read

    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char str[1024] = "AAA";
        // printf("Enter a number: ");
        // if (fgets(str, sizeof str, stdin))
        //     str[strcspn(str, "\n")] = '\0'; // TIP: swap \n with \0
        // printf("\n str is: %s \n", str);
        close(c_p[0]);
        close(1);
        dup(c_p[1]);
        write(1, str, strlen(str)+1);
    } else {
        wait(NULL);
        close(0);
        close(c_p[1]);
        dup(c_p[0]);
        char str[1024];
        int status_code = read(c_p[0], str, strlen(str)+1);
        for ( i = 0;i < status_code; i++)
            printf("%c ", str[i]);
        // printf("%d child exited with status: %s \n", status_code, str);
    }
}
