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

void encode_cesar(char* msg, int key, size_t length, unsigned char *result){
    encryptor_cesar_t cesar;
    encryptor_cesar_init(&cesar, key);
    encryptor_cesar_encode(&cesar, msg, length, result);
    encryptor_cesar_uninit(&cesar);
}

void encode_vigenere(char* msg, char *key, size_t length, unsigned char *result){
    encryptor_vigenere_t vigenere;
    encryptor_vigenere_init(&vigenere, key, strlen(key));
    encryptor_vigenere_encode(&vigenere, msg, length, result);
    encryptor_vigenere_uninit(&vigenere);
}

void encode_arc4(char* msg, char *key, size_t length, unsigned char *result){
    encryptor_arc4_t arc4;
    encryptor_arc4_init(&arc4, key, strlen(key));
    encryptor_arc4_encode(&arc4, msg, length, result);
    encryptor_arc4_uninit(&arc4);
}

void encode(char *msg, 
            size_t msg_length, 
            char *method, 
            char *key, 
            unsigned char *result){
    if (! strcmp(method, "cesar")) {
        encode_cesar(msg, atoi(key), msg_length, result);
    } else if (! strcmp(method, "vigenere")) {
        encode_vigenere(msg, key, msg_length, result);
    } else if (! strcmp(method, "rc4")) {
        encode_arc4(msg, key, msg_length, result);
    }
}

int main(int argc, char const *argv[]) {
    //Parseando los argumentos de comando de linea
    const char *server_host = argv[1];
    const char *server_port = argv[2];
    char method[strlen(argv[3]) - METHOD_LENGTH];
    strcpy(method, &argv[3][METHOD_LENGTH]);
    char key[strlen(argv[4]) - KEY_LENGTH];
    strcpy(key, &argv[4][KEY_LENGTH]);

    char buffer[CHUNK_SIZE];
    memset(buffer, 0, CHUNK_SIZE * sizeof(char));
    FILE *file = stdin;
    socket_t socket;
    socket_init(&socket);
    socket_connect(&socket, server_host, server_port);
    while (! feof(file)) {
        size_t read = fread(buffer, 1, CHUNK_SIZE, file);
        unsigned char result[read];
        memset(result, 0, read * sizeof(unsigned char));
        encode(buffer, read, method, key, result);
         
        socket_send(&socket, (const char *)result, read);
    }
    socket_uninit(&socket);

    return 0;
}
