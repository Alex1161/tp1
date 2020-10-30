#ifndef __ARC4_H__
#define __ARC4_H__

#include <stddef.h>

typedef struct {
    char *key;
    size_t size_key;
    unsigned char *stream;
} encryptor_arc4_t;

int encryptor_arc4_init(encryptor_arc4_t *self, 
                        char *key, 
                        size_t size_key);

int encryptor_arc4_encode(encryptor_arc4_t *self, 
                          const char *message, 
                          size_t message_size, 
                          unsigned char *result,
                          size_t state);

int encryptor_arc4_decode(encryptor_arc4_t *self, 
                          unsigned char *code, 
                          size_t code_size, 
                          char *message,
                          size_t state);

int encryptor_arc4_uninit(encryptor_arc4_t *self);

#endif
