#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
      /*
       * server_fd - is a file descriptor for server socket, new_socket holds
       * file descriptor for new connections accepted by server
       * sockaddr_in address holds current information about the socket (IP, port
       * etc.) buffer is used to recieve / send data AF_INET is the adress family
       * for Ipv4.
       */
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

            char method[3], app[1024];
            sscanf(buffer, "%s %s", method, app);

            if(strcmp(method, "RUN") == 0){
                  printf("RUN: %s", app);
                  char command[1025];
                  snprintf(command, sizeof(command), "open %s &", app);
                  system(command);
            }

            close(new_socket);
      }

      return 0;
}
