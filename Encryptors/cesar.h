#ifndef __CESAR_H__
#define __CESAR_H__

typedef struct {
    int key;
} encryptor_cesar_t;

int encryptor_cesar_init(encryptor_cesar_t *self, int key);

int encode(encryptor_cesar_t *self, const char *message, const char *result);

int encryptor_cesar_uninit(encryptor_cesar_t *self);

#endif