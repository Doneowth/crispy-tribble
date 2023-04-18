// Dong Liang, 002128806
// Chih-Hsiang Li, 002198826
#include "types.h"
#include "user.h"
#include "stat.h"

int
main(int argc, char *argv[])
{
  int pid;
  int priority;

  for (int i = 0; i < 5; i++) {
    pid = fork();
    if (pid < 0) {
      printf(1, "ERROR: fork failed\n");
      exit();
    } 
    else if (pid == 0) {
      priority = (i % 3); // give priority by iteration RR
      renice(getpid(), priority); // set priority via renice
      for (int j = 0; j < 50; j++) {
        printf(1, "Process %d with priority %d is running, iteration %d\n", getpid(), priority, j);
        sleep(10); // Sleep to switch to other processes
      }
      exit();
    }
  }

  // Parent wait
  for (int i = 0; i < 5; i++) {
    wait(); // join one thread
  }

  exit();
}

