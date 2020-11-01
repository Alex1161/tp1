#ifndef __ENCRYPTOR_H__
#define __ENCRYPTOR_H__

#include <stddef.h>

typedef struct {
    char *name;
    unsigned char *key;
    size_t state;
} encryptor_t;

int encryptor_init(encryptor_t *self, char *name, unsigned char *key);

int encryptor_encode(encryptor_t *self, 
                     unsigned char *msg, 
                     size_t msg_length, 
                     unsigned char *result);

int encryptor_decode(encryptor_t *self, 
                     unsigned char *code, 
                     size_t code_length, 
                     unsigned char *result);

int encryptor_uninit(encryptor_t *self);

#endif
