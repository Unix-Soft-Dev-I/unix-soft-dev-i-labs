#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv) 
{
  int fd;
  char* shared_fifo = "/tmp/named_pipe_shared_fifo";

  fd = open(shared_fifo, O_RDONLY);

  if (fd == -1) 
  {
    perror("Error opening fifo");

    return 1;
  }

  int r_elems[10];

  if (read(fd, r_elems, sizeof(int) * 10) == -1) 
  {
    perror("Error reading from fifo");

    return 1;
  }

  for (int i = 0; i < 10; i++) 
  {
    printf("%d ", r_elems[i]);
  }
  printf("\n");

  close(fd);

  return 0;
}
