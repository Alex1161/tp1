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
static void decode_vigenere(unsigned char* msg, 
                     char *key, 
                     size_t length, 
                     char *result);
static void decode_arc4(unsigned char* msg, 
                        char *key, 
                        size_t length, 
                        char *result);

static void encode_cesar(char* msg, 
                         int key, 
                         size_t length, 
                         unsigned char *result);
static void encode_vigenere(char* msg, 
                     char *key, 
                     size_t length, 
                     unsigned char *result);
static void encode_arc4(char* msg, 
                        char *key, 
                        size_t length, 
                        unsigned char *result);

/*---------------------------------------------------------------------------
  ------------------------- FUNCTIONS DEFINITIONS ---------------------------
  ---------------------------------------------------------------------------*/

int encryptor_init(encryptor_t *self, char *name, char *key){
    self->name = name;
    self->key = key;

    return 0;
}

int encryptor_encode(encryptor_t *self, 
                     char *msg, 
                     size_t msg_length, 
                     unsigned char *result) {
    if (! strcmp(self->name, "cesar")) {
        encode_cesar(msg, atoi(self->key), msg_length, result);
    } else if (! strcmp(self->name, "vigenere")) {
        encode_vigenere(msg, self->key, msg_length, result);
    } else if (! strcmp(self->name, "rc4")) {
        encode_arc4(msg, self->key, msg_length, result);
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
        decode_cesar((unsigned char*)code, atoi(self->key), code_length, result);
    } else if (! strcmp(self->name, "vigenere")) {
        decode_vigenere((unsigned char*)code, self->key, code_length, result);
    } else if (! strcmp(self->name, "rc4")) {
        decode_arc4((unsigned char*)code, self->key, code_length, result);
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

static void decode_vigenere(unsigned char* msg, 
                     char *key, 
                     size_t length, 
                     char *result) {
    encryptor_vigenere_t vigenere;
    encryptor_vigenere_init(&vigenere, key, strlen(key));
    encryptor_vigenere_decode(&vigenere, msg, length, result);
    encryptor_vigenere_uninit(&vigenere);
}

static void decode_arc4(unsigned char* msg, 
                        char *key, 
                        size_t length, 
                        char *result) {
    encryptor_arc4_t arc4;
    encryptor_arc4_init(&arc4, key, strlen(key));
    encryptor_arc4_decode(&arc4, msg, length, result);
    encryptor_arc4_uninit(&arc4);
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

static void encode_vigenere(char* msg, 
                     char *key, 
                     size_t length, 
                     unsigned char *result) {
    encryptor_vigenere_t vigenere;
    encryptor_vigenere_init(&vigenere, key, strlen(key));
    encryptor_vigenere_encode(&vigenere, msg, length, result);
    encryptor_vigenere_uninit(&vigenere);
}

static void encode_arc4(char* msg, 
                        char *key, 
                        size_t length, 
                        unsigned char *result) {
    encryptor_arc4_t arc4;
    encryptor_arc4_init(&arc4, key, strlen(key));
    encryptor_arc4_encode(&arc4, msg, length, result);
    encryptor_arc4_uninit(&arc4);
}
