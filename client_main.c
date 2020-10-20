#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "common_encryptor.h"
#include "common_socket.h"

const int METHOD_LENGTH = 9;
const int KEY_LENGTH = 6;
const size_t CHUNK_SIZE = 64;

int main(int argc, char const *argv[]) {
    //Parseando los argumentos de comando de linea
    const char *server_host = argv[1];
    const char *server_port = argv[2];
    char method[strlen(argv[3]) - METHOD_LENGTH];
    strncpy(method, 
            &argv[3][METHOD_LENGTH], 
            strlen(argv[3]) - METHOD_LENGTH + 1);
    char key[strlen(argv[4]) - KEY_LENGTH];
    strncpy(key, &argv[4][KEY_LENGTH], strlen(argv[4]) - KEY_LENGTH + 1);

    char buffer[CHUNK_SIZE];
    memset(buffer, 0, CHUNK_SIZE * sizeof(char));

    //calcular el tamaño del archivo
    fseek(stdin, 0, SEEK_END);
    size_t file_size = ftell(stdin);
    rewind(stdin);
    char *msg = malloc((file_size + 1) * sizeof(char));
    msg[0] = '\0';

    while (! feof(stdin)) {
        size_t read = fread(buffer, 1, CHUNK_SIZE, stdin);
        strncat(msg, buffer, read);
    }

    socket_t socket;
    socket_init(&socket);
    socket_connect(&socket, server_host, server_port);
    unsigned char *result = malloc(file_size * sizeof(unsigned char));

    encryptor_t encryptor;
    encryptor_init(&encryptor, method, key);
    encryptor_encode(&encryptor, msg, file_size, result);
    socket_send(&socket, (const char *)result, file_size);

    encryptor_uninit(&encryptor);
    free(result);
    free(msg);
    socket_uninit(&socket);

    return 0;
}
