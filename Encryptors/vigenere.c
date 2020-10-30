#include "vigenere.h"
#include "../Op_vec/op_vec.h"
#include <stdlib.h>

int encryptor_vigenere_init(encryptor_vigenere_t * self, 
                            char *key, 
                            size_t size_key) {
    self->key = key;
    self->size_key = size_key;

    return 0;
}

int encryptor_vigenere_encode(encryptor_vigenere_t *self, 
                              const char *message, 
                              size_t message_size, 
                              unsigned char *result,
                              size_t state) {
    for (size_t i = 0; i < message_size; i++) {
        result[i] = message[i] + self->key[(i + state) % self->size_key];
    }

    return 0;
}

int encryptor_vigenere_decode(encryptor_vigenere_t *self,
                              unsigned char *code, 
                              size_t code_size, 
                              char *message,
                              size_t state){
    for (size_t i = 0; i < code_size; i++) {
        message[i] = code[i] - self->key[(i + state) % self->size_key];
    }

    return 0;
}

int encryptor_vigenere_uninit(encryptor_vigenere_t *self) {
    //Do nothing
    return 0;
}
