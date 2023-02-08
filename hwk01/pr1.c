#include <stdio.h>
// Dong Liang
// 002128806

void 
print_args(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
        printf("argc[%d] = '%s'\n", i, *argv++);
}

int 
main(int argc, char **argv)                                            
{                                                                        
    print_args(argc, argv);                                          
    return 0;                                                        
}


