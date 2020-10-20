#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "common_encryptor.h"
#include "common_socket.h"

const int METHOD_LENGTH = 9;
const int KEY_LENGTH = 6;
const size_t MAX_LENGTH = 1000;

int main(int argc, char const *argv[]) {
    //Parseando los argumentos de comando de linea
    const char *server_port = argv[1];
    char method[strlen(argv[2]) - METHOD_LENGTH];
    strncpy(method, 
            &argv[2][METHOD_LENGTH], 
            strlen(argv[2]) - METHOD_LENGTH + 1);
    char key[strlen(argv[3]) - KEY_LENGTH];
    strncpy(key, &argv[3][KEY_LENGTH], strlen(argv[3]) - KEY_LENGTH + 1);

    socket_t socket;
    socket_init(&socket);
    socket_bind_listen(&socket, server_port);

    socket_t peer;
    socket_init(&peer);
    socket_accept(&socket, &peer);

    char buffer[MAX_LENGTH];
    memset(buffer, 0, MAX_LENGTH * sizeof(char));
    int received = socket_receive(&peer, buffer, MAX_LENGTH);;
    char *result = malloc(received * sizeof(char));
    memset(result, 0, received * sizeof(char));
    
    encryptor_t encryptor;
    encryptor_init(&encryptor, method, key);
    encryptor_decode(&encryptor, buffer, received, result);
    fwrite(result, 1, received, stdout);

    encryptor_uninit(&encryptor);
    free(result);
    socket_uninit(&peer);
    socket_uninit(&socket);

    return 0;
}
