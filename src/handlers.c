#include "handlers.h"
#include "db.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

void handle_post_req(int client_fd) {
    char *source = connect_and_fetch();
    if (!source) {
        const char *err_resp =
            "HTTP/1.1 500 Internal Server Error\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 21\r\n"
            "\r\n"
            "Something went wrong\n";
        write(client_fd, err_resp, strlen(err_resp));
        return;
    }

    printf("We did it: %s\n", source);

    char body[1024];
    int  body_len = snprintf(body, sizeof(body),
                             "<html><body>Result: %s</body></html>",
                             source);
    free(source);

    char header[256];
    int  header_len = snprintf(header, sizeof(header),
                               "HTTP/1.1 200 OK\r\n"
                               "Content-Type: text/html; charset=utf-8\r\n"
                               "Content-Length: %d\r\n"
                               "\r\n",
                               body_len);

    write(client_fd, header, header_len);
    write(client_fd, body, body_len);
}

void handle_404(int socket) {
  char *response = "HTTP/1.1 404 Not Found\r\n"
                   "Content-Type: text/html\r\n"
                   "Content-Length: 9\r\n"
                   "\r\n"
                   "Not found";
  write(socket, response, strlen(response));
}
