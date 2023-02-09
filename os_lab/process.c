#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int 
main()
{

	// make two process which run same
	// program after this instruction
	printf("Hello world!\n");
	
	fork() && fork();

	return 0;
}
