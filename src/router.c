#include "router.h"
#include "handlers.h"
#include <string.h>

void route_request(const char *method, const char *path, int socket) {
  if (strcmp(path, "/") == 0) {
    handle_root_dir(socket);
  } else if (strcmp(path, "/about") == 0) {
    handle_about_dir(socket);
  } else if (strcmp(path, "/post") == 0 && strcmp(method, "POST") == 0) {
    handle_post_req(socket);
  } else {
    handle_404(socket);
  }
}
