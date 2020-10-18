#include "arc4.h"
#include "../Op_vec/op_vec.h"
#include <stdlib.h>
const size_t STREAM_SIZE = 256;

/*------------------------------------------------------------------------
  ------------------------- AUXILIAR FUNCTIONS ---------------------------
  ------------------------------------------------------------------------*/

static void ksa(encryptor_arc4_t *self) {
    size_t i = 0;
    size_t j = 0;
    for (i = 0; i < STREAM_SIZE; i++) {
        self->stream[i] = i;
    }
 
    for (i = 0; i < STREAM_SIZE; i++) {
        j = (j + self->key[i % self->size_key] + self->stream[i]) % STREAM_SIZE;
        swap(self->stream, i, j);
    }
}

// static unsigned char prga(unsigned char *stream, size_t i, size_t j) {
//     i = (i + 1) % STREAM_SIZE;
//     j = (j + stream[i]) % STREAM_SIZE;

//     swap(stream, i, j);

//     return stream[(stream[i] + stream[j]) % STREAM_SIZE];
//}

static int gen_key_stream(unsigned char *stream, 
                          unsigned char *key_stream, 
                          size_t size_message){
    size_t i = 0;
    size_t j = 0;
    for (size_t k = 0; k < size_message; k++) {
        i = (i + 1) % STREAM_SIZE;
        j = (j + stream[i]) % STREAM_SIZE;

        swap(stream, i, j);

        key_stream[k] = stream[(stream[i] + stream[j]) % STREAM_SIZE];
    }
    
    return 0;
}

/*------------------------------------------------------------------------
  ----------------------- FUNCTIONS DEFINITIONS --------------------------
  ------------------------------------------------------------------------*/

int encryptor_arc4_init(encryptor_arc4_t *self, 
                        char *key, 
                        size_t size_key){
    self->key = key;
    self->size_key = size_key;
    self->stream = malloc(STREAM_SIZE * sizeof(unsigned char));

    return 0;
}

int encryptor_arc4_encode(encryptor_arc4_t *self, 
                          const char *message, 
                          size_t message_size, 
                          unsigned char *result) {
    ksa(self);
    unsigned char key_stream[message_size];
    gen_key_stream(self->stream, key_stream, message_size);

    xor(message, key_stream, result, message_size);
    
    return 0;
}

int encryptor_arc4_decode(encryptor_arc4_t *self, 
                          unsigned char *code, 
                          size_t code_size, 
                          char *message) {
    encryptor_arc4_encode(self, 
                          (const char *)code, 
                          code_size, 
                          (unsigned char *)message);
    return 0;
}

int encryptor_arc4_uninit(encryptor_arc4_t *self){
    free(self->stream);
    return 0;
}
