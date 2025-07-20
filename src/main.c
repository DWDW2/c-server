#include "router.h"
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
  char buffer[3000];

  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);
  // here we bind server file descriptor to a specific adress in ALL local IPs.
  bind(server_fd, (struct sockaddr *)&address, sizeof(address));
  // listening in server_fd
  listen(server_fd, 3);
  //  accepting new connections
  //  you can see that we create new socket
  //  in this new socket we can read / write stuff
  while (1) {
    new_socket =
        accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    memset(buffer, 0, sizeof(buffer));
    // here we're reading for buffer of size 3000
    read(new_socket, buffer, 3000);

    char method[8], path[1024];
    sscanf(buffer, "%s %s", method, path);

    printf("Buffer: %s %s\n", method, path);

    route_request(method, path, new_socket);

    close(new_socket);
  }

  return 0;
}
