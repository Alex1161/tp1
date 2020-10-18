#ifndef __OP_VEC_H__
#define __OP_VEC_H__

#include <stddef.h>

// Transforma un valor entero en un string con su representacion en hexadecimal
char* itoa(int value, char* result, int base);

// Transforma de unsigned char a un string de su valor numerico en hexadecimal
size_t un_char_to_hexa(unsigned char *element, char *hexa, size_t size_element);

// Transforma de unsigned char a bytes
size_t un_char_to_bytes(unsigned char *element, int *bytes, size_t size_element);

// Transforma de bytes a unsigned char
size_t bytes_to_un_char(int *bytes, unsigned char *result, size_t size_bytes);

// Alinea los bytes de la clave a la cantidad de bytes del mensaje y retorna su tamaño
size_t align(int *bytes_key, 
             int *bytes_key_aligned, 
             size_t size_bytes_msg, 
             size_t size_bytes_key);

// Suma byte a byte 2 arreglos del mismo tamaño y los guarda en result y retorna el tamaño
size_t sum(int *bytes1, int *bytes2, int *result, size_t size);

// Resta byte a byte 2 arreglos del mismo tamaño y los guarda en result y retorna el tamaño
size_t sub(int *bytes1, int *bytes2, int *result, size_t size);

// Hace xor elemento a alemento
size_t xor(const char *message, 
		   unsigned char *key_stream, 
		   unsigned char *result, 
		   size_t size);
           
// Intercambia el elemento de la posicion i con el de la posicion j
void swap(unsigned char *s, size_t i, size_t j);


#endif