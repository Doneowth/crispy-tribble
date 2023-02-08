#include <stdio.h>
#include <string.h>
// Dong Liang
// 002128806
int 
main(int argc, char **argv)                                            
{     
    char line[1000];

    printf("$ ");
    while(fgets(line, sizeof(line), stdin) && line[0] != '\n')
    {
        printf("%s", line);
        printf("$ ");
    }                                                              

    return 0;
}
