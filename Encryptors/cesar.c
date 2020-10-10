#include "cesar.h"

int encryptor_cesar_init(encryptor_cesar_t * self, int key) {
    self->key = key;
    return 0;
}

int encode(encryptor_cesar_t *self, const char *message, const char *result) {
    result = message;
    return 0;
}

int encryptor_cesar_uninit(encryptor_cesar_t *self) {
    //Do nothing
    return 0;
}