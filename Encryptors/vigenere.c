#include "vigenere.h"
#include "../Op_vec/op_vec.h"
#include <stdlib.h>

int encryptor_vigenere_init(encryptor_vigenere_t * self, 
                            char *key, 
                            size_t size_key) {
    self->key = key;
    self->size_key = size_key;
    self->estado = 0;
    return 0;
}

int encryptor_vigenere_encode(encryptor_vigenere_t *self, 
                              const char *message, 
                              size_t message_size, 
                              unsigned char *result) {
    size_t i;
    for (i = 0; i < message_size; i++) {
        result[i] = message[i] + self->key[(i + self->estado) % self->size_key];
    }

    self->estado = i;
    return 0;
}

int encryptor_vigenere_decode(encryptor_vigenere_t *self,
                              unsigned char *code, 
                              size_t code_size, 
                              char *message){
    // Paso el code y la key a bytes
    int *bytes_code = malloc(code_size * sizeof(int));
    size_t size_bytes_code = un_char_to_bytes(code, 
                                             bytes_code, 
                                             code_size);

    int *bytes_key = malloc(self->size_key * sizeof(int));
    size_t size_bytes_key = un_char_to_bytes((unsigned char *)self->key, 
                                             bytes_key, 
                                             self->size_key);


    // Alineo el tamaño de la key con el tamaño del code
    int *bytes_key_aligned = malloc(size_bytes_code * sizeof(int));
    size_t size_bytes_key_aligned = align(bytes_key, 
                                          bytes_key_aligned, 
                                          size_bytes_code, 
                                          size_bytes_key);

    // Resto el code con la key alineada byte a byte
    int *bytes_decoded = malloc(size_bytes_key_aligned * sizeof(int));
    size_t size_bytes_decoded = sub(bytes_code, 
                                    bytes_key_aligned, 
                                    bytes_decoded, 
                                    size_bytes_code);

    // Transformo a char
    bytes_to_un_char(bytes_decoded, 
                     (unsigned char *)message, 
                     size_bytes_decoded);

    free(bytes_decoded);
    free(bytes_key_aligned);
    free(bytes_key);
    free(bytes_code);
    return 0;
}

int encryptor_vigenere_uninit(encryptor_vigenere_t *self) {
    //Do nothing
    return 0;
}
