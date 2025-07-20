#ifndef HANDLERS_H
#define HANDLERS_H

void handle_root_dir(int socket);
void handle_about_dir(int socket);
void handle_post_req(int socket);
void handle_404(int socket);

#endif
