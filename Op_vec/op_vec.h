#ifndef __OP_VEC_H__
#define __OP_VEC_H__

#include <stddef.h>

// Transforma un valor entero en un string con su representacion en la base
// especificada.
char* itoa(int value, char* result, int base);

// Transforma de unsigned char a un string de su valor numerico en hexadecimal
size_t un_char_to_hexa(unsigned char *element, char *hexa, size_t size_element);

// Transforma de unsigned char a bytes
size_t un_char_to_bytes(unsigned char *element, 
                        int *bytes, 
                        size_t size_element);

// Transforma de bytes a unsigned char
size_t bytes_to_un_char(int *bytes, unsigned char *result, size_t size_bytes);

#endif
