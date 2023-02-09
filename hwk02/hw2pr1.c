#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define BUFFSIZE PIPE_BUF
// Dong Liang
// 002128806
int 
main() 
{ 
  int i; 
  int pc[2];
  int cp[2];

  int p2c = pipe(pc);
  int c2p = pipe(cp);

  int pid = fork(); 

  char string[] = "L";
  
  if (pid < 0)
    perror("pipe");

  if (pid == 0) { 
    // close child read & child write
    close(cp[0]);
    close(pc[1]);

    for (i = 0; i < 5; i++) {
      // child recv from parent
      // int c = read(pc[0], string, (strlen(string)+1));  

      // this can be used to determine which process will get excuted 
      if (i > 0) {
        int c = read(pc[0], string, (strlen(string)+1));  
      } 


      // print child info
      printf("%d. Child\n", i + 1); 
      fflush(stdout);

      // child send to parent
      write(cp[1], string, (strlen(string)+1));
    } 
  } 
  else { 
    // close unwanted pipe ends for parent
    close(pc[0]) ;
    close(cp[1]);

    for (i = 0; i < 5; i++) { 


      // parent recv from child
      // if (i > 0) {
        int p = read(cp[0], string, (strlen(string)+1));
      // }

      // print parent info
      printf("%d. Parent\n", i + 1); 
      fflush(stdout);      
      
      // parent send to child
      write(pc[1], string, (strlen(string)+1));
    }
    wait(NULL); 
  } 
}