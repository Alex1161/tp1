#include <stdio.h>
#include <stdbool.h>
#include "common_socket.h"

int main(int argc, char const *argv[]) {
    socket_t socket;
    int status;
    status = socket_init(&socket);
    if (status == -1) {
        printf("No inicializo bien\n");
    }
    
    status = socket_connect(&socket, "localhost", "7777");
    if (status == -1) {
        printf("No conecto bien\n");
    }
    status = socket_send(&socket, "Hola mundo!\n", 12);
    if (status == -1) {
        printf("No envio bien\n");
    }

    socket_uninit(&socket);
    return 0;
}
