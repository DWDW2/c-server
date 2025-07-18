#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
  int server_fd, new_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[3000] = {0};
  char *response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html\r\n"
                   "Content-Length: 13\r\n"
                   "\r\n"
                   "Hello, world!";

  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);
  bind(server_fd, (struct sockaddr *)&address, sizeof(address));

  listen(server_fd, 3);

  while (1) {
    new_socket =
        accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    read(new_socket, buffer, 3000);

    write(new_socket, response, strlen(response));

    close(new_socket);
  }

  return 0;
}
