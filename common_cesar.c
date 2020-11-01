#include "common_cesar.h"
#include <string.h>

int encryptor_cesar_init(encryptor_cesar_t * self, int key) {
    self->key = key;
    
    return 0;
}

int encryptor_cesar_encode(encryptor_cesar_t *self, 
                           const unsigned char *message, 
                           size_t message_size,
                           unsigned char *result) {
    for (int i = 0; i < message_size; i++) {
        unsigned char act;
        act = message[i];
        result[i] = ((act + self->key) % 256);
    }

    return 0;
}

int encryptor_cesar_decode(encryptor_cesar_t *self,
                           unsigned char *code, 
                           size_t code_size, 
                           unsigned char *message){
    for (int i = 0; i < code_size; i++) {
        unsigned char act;
        act = code[i];
        message[i] = ((act - self->key) % 256);
    }

    return 0;
}

int encryptor_cesar_uninit(encryptor_cesar_t *self) {
    //Do nothing
    return 0;
}
