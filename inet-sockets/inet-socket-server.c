#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 9595
#define MESSAGE_SIZE 128

int main(int argv, char** argc)
{
  int server_socket_fd;
  // int port = 9595;

  server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server_socket_fd == -1)
  {
    perror("Error at socket creation.");

    return 1;
  }

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  int bind_status = bind(server_socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));

  if (bind_status == -1)
  {
    perror("Error at socket bind.");

    return 1;
  }

  int listen_status = listen(server_socket_fd, 5);

  if (listen_status == -1)
  {
    perror("Error at listen.");

    return 1;
  }

  int client_socket_fd;
  struct sockaddr_in client_addr;
  int size_client_addr = sizeof(client_addr);

  client_socket_fd = accept(server_socket_fd, (struct sockaddr*) &client_addr, (socklen_t *) &size_client_addr);

  if (client_socket_fd == -1)
  {
    perror("Error acepting client.");

    return 1;
  }

  char request[MESSAGE_SIZE];
  int read_status = read(client_socket_fd, &request, MESSAGE_SIZE);

  if (read_status == -1)
  {
    perror("Error reading request.");

    return 1;
  }

  printf("Request from client: %s\n", request);

  char response[MESSAGE_SIZE] = "What's up Client?";
  int write_status = write(client_socket_fd, response, MESSAGE_SIZE);

  if (write_status == -1)
  {
    perror("Error at response.");
    
    return 1;
  }

  close(client_socket_fd);
  close(server_socket_fd);

  return 0;
}
