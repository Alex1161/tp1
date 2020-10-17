#include "cesar.h"
#include <string.h>

int encryptor_cesar_init(encryptor_cesar_t * self, int key) {
    self->key = key;
    return 0;
}

int encode(encryptor_cesar_t *self, 
           const char *message, 
           size_t message_size,
           unsigned char *result) {
    unsigned char act;

    for (int i = 0; i < message_size; i++) {
        act = (unsigned char)message[i];
        result[i] = (char)((act + self->key) % 256);
    }

    return 0;
}

int decode(encryptor_cesar_t *self,
           unsigned char *code, 
           size_t code_size , 
           char *message){
    unsigned char act;
    for (int i = 0; i < code_size; i++) {
        act = (unsigned char)code[i];
        message[i] = (char)((act - self->key) % 256);
    }

    return 0;
}

int encryptor_cesar_uninit(encryptor_cesar_t *self) {
    //Do nothing
    return 0;
}