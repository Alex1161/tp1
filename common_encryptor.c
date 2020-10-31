#include "common_encryptor.h"
#include <string.h>
#include <stdlib.h>
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_arc4.h"

/*---------------------------------------------------------------------------
  ------------------ AUXILIAR FUNCTIONS DECLARATIONS ------------------------
  ---------------------------------------------------------------------------*/

static void decode_cesar(unsigned char* msg, 
                         int key, 
                         size_t length, 
                         char *result);
static void decode_vigenere(encryptor_t *self,
                            unsigned char* msg, 
                            size_t length, 
                            char *result);
static void decode_arc4(encryptor_t *self,
                        unsigned char* msg, 
                        size_t length, 
                        char *result);

static void encode_cesar(char* msg, 
                         int key, 
                         size_t length, 
                         unsigned char *result);
static void encode_vigenere(encryptor_t *self,
                            char* msg, 
                            size_t length, 
                            unsigned char *result);
static void encode_arc4(encryptor_t *self,
                        char* msg, 
                        size_t length, 
                        unsigned char *result);

/*---------------------------------------------------------------------------
  ------------------------- FUNCTIONS DEFINITIONS ---------------------------
  ---------------------------------------------------------------------------*/

int encryptor_init(encryptor_t *self, char *name, char *key){
    self->name = name;
    self->key = key;
    self->state = 0;

    return 0;
}

int encryptor_encode(encryptor_t *self, 
                     char *msg, 
                     size_t msg_length, 
                     unsigned char *result) {
    if (! strcmp(self->name, "cesar")) {
        encode_cesar(msg, strtol(self->key, NULL, 10), msg_length, result);
    } else if (! strcmp(self->name, "vigenere")) {
        encode_vigenere(self, msg, msg_length, result);
    } else if (! strcmp(self->name, "rc4")) {
        encode_arc4(self, msg, msg_length, result);
    } else {
        return 1;
    }

    return 0;
}


int encryptor_decode(encryptor_t *self, 
                     char *code, 
                     size_t code_length, 
                     char *result) {
    if (! strcmp(self->name, "cesar")) {
        decode_cesar((unsigned char*)code, 
                     strtol(self->key, NULL, 10), 
                     code_length, 
                     result);
    } else if (! strcmp(self->name, "vigenere")) {
        decode_vigenere(self, (unsigned char*)code, code_length, result);
    } else if (! strcmp(self->name, "rc4")) {
        decode_arc4(self, (unsigned char*)code, code_length, result);
    } else {
        return 1;
    }

    return 0;
}

int encryptor_uninit(encryptor_t *self){
    // Do nothing
    return 0;
}

/*---------------------------------------------------------------------------
  ------------------ AUXILIAR FUNCTIONS DEFINITIONS -------------------------
  ---------------------------------------------------------------------------*/

static void decode_cesar(unsigned char* msg, 
                         int key, 
                         size_t length, 
                         char *result) {
    encryptor_cesar_t cesar;
    encryptor_cesar_init(&cesar, key);
    encryptor_cesar_decode(&cesar, msg, length, result);
    encryptor_cesar_uninit(&cesar);
}

static void decode_vigenere(encryptor_t *self,
                            unsigned char* msg, 
                            size_t length, 
                            char *result) {
    encryptor_vigenere_t vigenere;
    encryptor_vigenere_init(&vigenere, self->key, strlen(self->key));
    encryptor_vigenere_decode(&vigenere, msg, length, result, self->state);
    encryptor_vigenere_uninit(&vigenere);

    self->state = length;
}

static void decode_arc4(encryptor_t *self,
                        unsigned char* msg, 
                        size_t length, 
                        char *result) {
    encryptor_arc4_t arc4;
    encryptor_arc4_init(&arc4, self->key, strlen(self->key));
    encryptor_arc4_decode(&arc4, msg, length, result, self->state);
    encryptor_arc4_uninit(&arc4);

    self->state = length;
}

static void encode_cesar(char* msg, 
                         int key, 
                         size_t length, 
                         unsigned char *result) {
    encryptor_cesar_t cesar;
    encryptor_cesar_init(&cesar, key);
    encryptor_cesar_encode(&cesar, msg, length, result);
    encryptor_cesar_uninit(&cesar);
}

static void encode_vigenere(encryptor_t *self,
                            char* msg, 
                            size_t length, 
                            unsigned char *result) {
    encryptor_vigenere_t vigenere;
    encryptor_vigenere_init(&vigenere, self->key, strlen(self->key));
    encryptor_vigenere_encode(&vigenere, msg, length, result, self->state);
    encryptor_vigenere_uninit(&vigenere);

    self->state = length;
}

static void encode_arc4(encryptor_t *self,
                        char* msg, 
                        size_t length, 
                        unsigned char *result) {
    encryptor_arc4_t arc4;
    encryptor_arc4_init(&arc4, self->key, strlen(self->key));
    encryptor_arc4_encode(&arc4, msg, length, result, self->state);
    encryptor_arc4_uninit(&arc4);

    self->state = length;
}
