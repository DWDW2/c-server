#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8080

struct Headers {
   char *host;
   char *method;
   char *cache_control;
   char *user_agent;
} typedef headers_t;

void init_headers(headers_t *hd){
   if(hd){
      hd->cache_control = NULL;
      hd->host= NULL;
      hd->method = NULL;
      hd->user_agent = NULL;
   }
}

void http_parse(char *request){
   headers_t hd; 
   init_headers(&hd);
   char *line;
   char *res = request;

   line = strtok(res, "\n");

   while(line != NULL){
      char header_name[1000];
      char header_value[2000];
   
      int scanned = sscanf(line, "%s %s", header_name, header_value); 
   
      if(scanned > 0){
         for(int i = 0; header_name[i] != '\0'; i++){
            if(header_name[i] == ':'){
               header_name[i] = '\0'; 
            }
         }
      } 

      if(strcmp(header_name, "User-Agent") == 0){
         hd.user_agent = header_value; 
      }

      line = strtok(NULL, "\n");
   }
}


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


      pthread_t pthread_id;
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

            http_parse(buffer);  

            close(new_socket);
      }

      return 0;
}
