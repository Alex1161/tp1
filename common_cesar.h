#ifndef __CESAR_H__
#define __CESAR_H__

#include <stddef.h>

typedef struct {
    int key;
} encryptor_cesar_t;

int encryptor_cesar_init(encryptor_cesar_t *self, int key);

int encryptor_cesar_encode(encryptor_cesar_t *self, 
                           const unsigned char *message, 
                           size_t message_size, 
                           unsigned char *result);

int encryptor_cesar_decode(encryptor_cesar_t *self, 
                           unsigned char *code, 
                           size_t code_size, 
                           unsigned char *message);

int encryptor_cesar_uninit(encryptor_cesar_t *self);

#endif
