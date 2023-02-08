#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Dong Liang
// 002128806
void 
print_args(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
        printf("argc[%d] = '%s' \n", i, *argv++);
}


int
get_args(char *in, char **argv, int max_args) 
{
    int count = 0;
    char *str = strtok(in, " "); 
    strcpy(argv[count++], strdup(str)); 
    while (count < max_args) {
        str = strtok(NULL, " ");
        if (str != NULL) {
            char *tmp = strdup(str); 
            strcpy(argv[count++], tmp);

        } else {
            break;
        }
    }
    return count;
}


int 
main()                                            
{                                                                        
    char s[200];
    char *argv[10];
    for(int i=0; i<10; i++ ) 
        argv[i] = (char*) malloc(sizeof(char) * 100);

    int argc;

    printf("Enter a string: ");
    fgets(s, sizeof s, stdin);

    argc = get_args(s, argv, 10);
    print_args(argc, argv);                                          
    
    return 0;                                                        
}


