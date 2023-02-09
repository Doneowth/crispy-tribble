#include <stdio.h>
#include <string.h>
// Dong Liang
// 002128806
int 
main(int argc, char **argv)                                            
{     
    char line[1000];
    printf("$ ");
    while(fgets(line, sizeof line, stdin) && line[0] != '\n')
    {
        printf("%s\n", line);
        // printf("input str length: %ld\n", strlen(line));
        // printf("last 2 digits are: %c %c\n", line[strlen(line) - 2], line[strlen(line) - 1]);
        // THINK: it seems that fgets will scan NT(null-terminator) in
        printf("$ ");
    }                                                              

    return 0;
}
