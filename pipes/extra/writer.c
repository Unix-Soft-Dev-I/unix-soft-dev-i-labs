#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FileName "data.txt"
#define DataString "This is a text created using Pipes,\nwith a flock struct and fcntl function to manipulate the file.\n"

int main(int argc, char** argv) 
{
  struct flock lock;
  lock.l_type = F_WRLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0; 
  lock.l_pid = getpid();

  int fd = open(FileName, O_RDWR | O_CREAT, 0666);

  if (fd == -1)
  {
    perror("Error opening fifo.");

    return 1;
  }

  int file_control_status = fcntl(fd, F_SETLK, &lock);

  if (file_control_status == -1)
  {
    perror("Failed to get lock.");

    return 1;
  }
  else {
    write(fd, DataString, strlen(DataString));
    fprintf(stderr, "Process %d has written to data file.\n", lock.l_pid);
  }

  lock.l_type = F_UNLCK;

  if (file_control_status == -1)
  {
    perror("Explicit unlocking failed.");
    
    return 1;
  }

  close(fd);

  return 0;
}
