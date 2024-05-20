#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv) 
{
  int fd;
  char* shared_fifo = "/tmp/named_pipe_shared_fifo";
  int fifo_status = mkfifo(shared_fifo, 0666);

  if (fifo_status == -1) 
  {
    perror("Error creating fifo.");

    return 1;
  }

  fd = open(shared_fifo, O_WRONLY);

  if (fd == -1) 
  {
    perror("Error opening fifo.");

    return 1;
  }

  int w_elems[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  if (write(fd, w_elems, sizeof(int) * 10) == -1) 
  {
    perror("Error writing to fifo.");

    close(fd);

    return 1;
  }

  close(fd);

  return 0;
}
