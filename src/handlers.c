#include "handlers.h"
#include "db.h"
#include <string.h>
#include <unistd.h>

void handle_root_dir(int socket) {
  char *response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html\r\n"
                   "Content-Length: 13\r\n"
                   "\r\n"
                   "Hello, world!";
  write(socket, response, strlen(response));
}

void handle_about_dir(int socket) {
  char *response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html\r\n"
                   "Content-Length: 13\r\n"
                   "\r\n"
                   "Hello, world!";
  write(socket, response, strlen(response));
}

void handle_post_req(int socket) {
  connect();
  char *response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html\r\n"
                   "Content-Length: 27\r\n"
                   "\r\n"
                   "YOU DID POST REQUEST IN C";
  write(socket, response, strlen(response));
}

void handle_404(int socket) {
  char *response = "HTTP/1.1 404 Not Found\r\n"
                   "Content-Type: text/html\r\n"
                   "Content-Length: 9\r\n"
                   "\r\n"
                   "Not found";
  write(socket, response, strlen(response));
}
