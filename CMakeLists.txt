cmake_minimum_required(VERSION 3.10)
project(SimpleHttpServer C)

set(CMAKE_C_STANDARD 99)

add_executable(http_server
    src/main.c
    src/handlers.c
    src/router.c
)
