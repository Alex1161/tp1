#ifndef __CESAR_H__
#define __CESAR_H__

#include <stddef.h>

typedef struct {
    int key;
} encryptor_cesar_t;

int encryptor_cesar_init(encryptor_cesar_t *self, int key);

int encode(encryptor_cesar_t *self, 
           const char *message, 
           size_t message_size, 
           unsigned char *result);

int decode(encryptor_cesar_t *self, 
           unsigned char *code, 
           size_t code_size, 
           char *message);

int encryptor_cesar_uninit(encryptor_cesar_t *self);

#endif