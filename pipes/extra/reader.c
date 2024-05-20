#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FileName "data.txt"

int main(int argc, char** argv) 
{
  struct flock lock;
  lock.l_type = F_WRLCK;    
  lock.l_whence = SEEK_SET; 
  lock.l_start = 0;         
  lock.l_len = 0;           
  lock.l_pid = getpid();    

  int fd = open(FileName, O_RDONLY);

  if (fd == -1) 
  {
    perror("Error opening fifo.");

    return 1; 
  }

  fcntl(fd, F_GETLK, &lock);

  if (lock.l_type != F_UNLCK)
  {
    perror("File is still write locked.");

    return 1;
  }

  lock.l_type = F_RDLCK;
  int file_control_status = fcntl(fd, F_SETLK, &lock);

  if (file_control_status == -1)
  {
    perror("Cannot get a read-only lock.");

    return 1;
  }

  int c; 
  while ((read(fd, &c, 1)) > 0)  
  {
    write(STDOUT_FILENO, &c, 1);
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
