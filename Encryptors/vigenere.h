#ifndef __VIGENERE_H__
#define __VIGENERE_H__

#include <stddef.h>

typedef struct {
    char *key;
    size_t size_key;
} encryptor_vigenere_t;

int encryptor_vigenere_init(encryptor_vigenere_t *self, 
                            char *key, 
                            size_t size_key);

int encryptor_vigenere_encode(encryptor_vigenere_t *self, 
                              const char *message, 
                              size_t message_size, 
                              unsigned char *result,
                              size_t state);

int encryptor_vigenere_decode(encryptor_vigenere_t *self, 
                              unsigned char *code, 
                              size_t code_size, 
                              char *message,
                              size_t state);

int encryptor_vigenere_uninit(encryptor_vigenere_t *self);

#endif
