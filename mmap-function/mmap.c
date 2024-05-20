#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv) 
{
	int fd = open("data.txt", O_RDONLY);
	if (fd == -1) 
	{
    perror("Error at opening the file.");
    
		return 1;
	}

	struct stat sb;
	if (fstat(fd, &sb) == -1) 
	{
    perror("Error at fstat.");
    
		return 1;
	}

	void *mapped = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (mapped == MAP_FAILED) 
	{
    perror("Error at mmap function.");
    
		return 1;
	}

	write(STDOUT_FILENO, mapped, sb.st_size);

	munmap(mapped, sb.st_size);
	close(fd);

	return 0;
}
