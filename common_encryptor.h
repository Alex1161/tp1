#ifndef __ENCRYPTOR_H__
#define __ENCRYPTOR_H__

#include <stddef.h>

typedef struct {
    char *name;
    char *key;
} encryptor_t;

int encryptor_init(encryptor_t *self, char *name, char *key);

int encryptor_encode(encryptor_t *self, 
                     char *msg, 
                     size_t msg_length, 
                     unsigned char *result);

int encryptor_decode(encryptor_t *self, 
                     char *code, 
                     size_t code_length, 
                     char *result);

int encryptor_uninit(encryptor_t *self);

#endif
