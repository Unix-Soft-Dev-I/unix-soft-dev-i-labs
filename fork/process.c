#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
  Assignment:
  - Create 3 processes using fork() that they finish execution in the correct order.
    In this case, a parent, child, and grandchild process.
    
    Grandchild -> Child
    Child -> Parent

  Extra:
  - I made each process prints a sequence of numbers based on its value of n.
    
    Grandchild: 1 to 5
    Child: 6 to 10
    Parent: 11 to 15
*/

int main(int argc, char** argv) 
{
  int n;
  printf("1. main process pid: %d, parent process pid: %d\n", getpid(), getppid());
  
  pid_t child_pid_status = fork();

  // child process
  if (child_pid_status == 0)
  {
    printf("at child process pid(%d), parent process pid(%d)\n", getpid(), getppid());
    n = 6;
    sleep(5);

    pid_t grandchild_pid_status = fork(); 

    // granchild process
    if (grandchild_pid_status == 0) 
    {
      printf("at grandchild process pid(%d), parent process pid(%d)\n", getpid(), getppid());
      n = 1;
      sleep(10);

      printf("Finish grandchild block\n");
    } else 
    {
      wait(NULL);

      printf("Finish child block\n");
    }
  } else 
  {
    // parent process
    n = 11;

    printf("2. main process pid(%d), parent process pid(%d)\n", getpid(), getppid());

    wait(NULL);

    printf("Finish parent block\n");
  }

  int i;

  for (i = n; i < n + 5; i++) 
  {
    printf("%d ", i);
    fflush(stdout);
  }
  printf("\n");

  printf("Finish main process pid(%d), parent process pid(%d).\n", getpid(), getppid());

  return 0;
}
