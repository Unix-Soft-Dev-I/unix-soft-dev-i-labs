#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 9595
#define MESSAGE_SIZE 128

int main(int argv, char** argc)
{
  int client_socket_fd;
  client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (client_socket_fd == -1)
  {
    perror("Error at socket creation");

    return 1;
  }

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  int connect_status = connect(client_socket_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

  if (connect_status == -1)
  {
    perror("Error at connection.");

    return 1;
  }

  char w_buffer[MESSAGE_SIZE] = "Hi Server!";
  int write_status = write(client_socket_fd, &w_buffer, MESSAGE_SIZE);

  if (write_status == -1)
  {
    perror("Error at write.");

    return 1;
  }

  char r_buffer[MESSAGE_SIZE];
  int read_status = read(client_socket_fd, &r_buffer, MESSAGE_SIZE);

  if (read_status == -1)
  {
    perror("Error at read.");

    return 1;
  }

  printf("Response from server: %s\n", r_buffer);

  close(client_socket_fd);

  return 0;
}
