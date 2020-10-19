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
    
    status = socket_bind_listen(&socket, "localhost", "7777");
    if (status == -1) {
        printf("No bindeo ni listeneo bien\n");
    }

    socket_t peer;
    socket_init(&peer);
    status = socket_accept(&socket, &peer);
    if (status == -1) {
        printf("No acepto bien\n");
    }

    char buffer[100];
    status = socket_receive(&peer, buffer, 100);
    if (status == -1) {
        printf("No recivio bien\n");
    }

    printf("%s", buffer);

    socket_uninit(&peer);
    socket_uninit(&socket);
    return 0;
}
