#include "vigenere.h"
#include "../Op_vec/op_vec.h"

int encryptor_vigenere_init(encryptor_vigenere_t * self, 
                            char *key, 
                            size_t size_key) {
    self->key = key;
    self->size_key = size_key;
    return 0;
}

int encryptor_vigenere_encode(encryptor_vigenere_t *self, 
                              const char *message, 
                              size_t message_size, 
                              unsigned char *result) {
    // pasar a numeros mensaje y key
    int bytes_message[message_size];
    size_t size_bytes_msg = un_char_to_bytes((unsigned char *)message, 
                                             bytes_message, 
                                             message_size);

    int bytes_key[self->size_key];
    size_t size_bytes_key = un_char_to_bytes((unsigned char *)self->key, 
                                             bytes_key, 
                                             self->size_key);

    // alinear el tamañano de key al tamñano del msg
    int bytes_key_aligned[size_bytes_msg];
    size_t size_bytes_key_aligned = align(bytes_key, 
                                          bytes_key_aligned, 
                                          size_bytes_msg, 
                                          size_bytes_key);

    // Sumar byte a byte
    int bytes_encoded[size_bytes_key_aligned];
    size_t size_bytes_encoded = sum(bytes_message, 
                                    bytes_key_aligned, 
                                    bytes_encoded, 
                                    size_bytes_msg);

    // Trasnformar a unsigned char
    bytes_to_un_char(bytes_encoded, result, size_bytes_encoded);

    return 0;
}

int encryptor_vigenere_decode(encryptor_vigenere_t *self,
                              unsigned char *code, 
                              size_t code_size, 
                              char *message){
    // Paso el code y la key a bytes
    int bytes_code[code_size];
    size_t size_bytes_code = un_char_to_bytes(code, 
                                             bytes_code, 
                                             code_size);

    int bytes_key[self->size_key];
    size_t size_bytes_key = un_char_to_bytes((unsigned char *)self->key, 
                                             bytes_key, 
                                             self->size_key);


    // Alineo el tamaño de la key con el tamaño del code
    int bytes_key_aligned[size_bytes_code];
    size_t size_bytes_key_aligned = align(bytes_key, 
                                          bytes_key_aligned, 
                                          size_bytes_code, 
                                          size_bytes_key);

    // Resto el code con la key alineada byte a byte
    int bytes_decoded[size_bytes_key_aligned];
    size_t size_bytes_decoded = sub(bytes_code, 
                                    bytes_key_aligned, 
                                    bytes_decoded, 
                                    size_bytes_code);

    // Transformo a char
    bytes_to_un_char(bytes_decoded, (unsigned char *)message, size_bytes_decoded);

    return 0;
}

int encryptor_vigenere_uninit(encryptor_vigenere_t *self) {
    //Do nothing
    return 0;
}