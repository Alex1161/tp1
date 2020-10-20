#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_arc4.h"
#include "common_socket.h"

const int METHOD_LENGTH = 9;
const int KEY_LENGTH = 6;
const size_t CHUNK_SIZE = 64;

void decode_cesar(unsigned char* msg, int key, size_t length, char *result){
    encryptor_cesar_t cesar;
    encryptor_cesar_init(&cesar, key);
    encryptor_cesar_decode(&cesar, msg, length, result);
    encryptor_cesar_uninit(&cesar);
}

void decode_vigenere(unsigned char* msg, char *key, size_t length, char *result){
    encryptor_vigenere_t vigenere;
    encryptor_vigenere_init(&vigenere, key, strlen(key));
    encryptor_vigenere_decode(&vigenere, msg, length, result);
    encryptor_vigenere_uninit(&vigenere);
}

void decode_arc4(unsigned char* msg, char *key, size_t length, char *result){
    encryptor_arc4_t arc4;
    encryptor_arc4_init(&arc4, key, strlen(key));
    encryptor_arc4_decode(&arc4, msg, length, result);
    encryptor_arc4_uninit(&arc4);
}


void decode(char *code, 
            size_t code_length, 
            char *method, 
            char *key, 
            char *result) {
    if (! strcmp(method, "cesar")) {
        decode_cesar((unsigned char*)code, atoi(key), code_length, result);
    } else if (! strcmp(method, "vigenere")) {
        decode_vigenere((unsigned char*)code, key, code_length, result);
    } else if (! strcmp(method, "rc4")) {
        decode_arc4((unsigned char*)code, key, code_length, result);
    }
}

int main(int argc, char const *argv[]) {
    //Parseando los argumentos de comando de linea
    const char *server_port = argv[1];
    char method[strlen(argv[2]) - METHOD_LENGTH];
    strcpy(method, &argv[2][METHOD_LENGTH]);
    char key[strlen(argv[3]) - KEY_LENGTH];
    strcpy(key, &argv[3][KEY_LENGTH]);

    socket_t socket;
    socket_init(&socket);
    socket_bind_listen(&socket, server_port);

    socket_t peer;
    socket_init(&peer);
    socket_accept(&socket, &peer);

    char buffer[CHUNK_SIZE];
    memset(buffer, 0, CHUNK_SIZE * sizeof(char));
    size_t received;
    received = socket_receive(&peer, buffer, CHUNK_SIZE);
    char result[received];
    memset(result, 0, received * sizeof(char));

    decode(buffer, received, method, key, result);
    fwrite(result, 1, received, stdout);

    socket_uninit(&peer);
    socket_uninit(&socket);

    return 0;

}
