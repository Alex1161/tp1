#include "common_op_vec.h"
#include <string.h>
#include <stdlib.h>

size_t un_char_to_bytes(unsigned char 
						*element, 
						int *bytes, 
						size_t size_element) {
	size_t size = 0;
	for (size = 0; size < size_element; size++) {
		bytes[size] = (int) element[size];
	}
	
	return size;
}

size_t bytes_to_un_char(int *bytes, unsigned char *result, size_t size_bytes) {
    size_t size = 0;
	for (size = 0; size < size_bytes; size++) {
		result[size] = (unsigned char) (bytes[size] % 256);
	}
	
	return size;
}

size_t align(int *bytes_key, 
             int *bytes_key_aligned, 
             size_t size_bytes_msg, 
             size_t size_bytes_key) {
    if (size_bytes_msg <= size_bytes_key) {
        for (size_t i = 0; i < size_bytes_msg; i++) {
            bytes_key_aligned[i] = bytes_key[i];
        }
    } else {
        for (size_t i = 0; i < size_bytes_key; i++) {
            bytes_key_aligned[i] = bytes_key[i];
        }

        for (size_t i = size_bytes_key; i < size_bytes_msg; i++) {
            bytes_key_aligned[i] = bytes_key[i % size_bytes_key];
        }
    }
    
    return size_bytes_msg;
}

size_t sum(int *bytes1, int *bytes2, int *result, size_t size) {
    for (size_t i = 0; i < size; i++) {
        result[i] = bytes1[i] + bytes2[i];
    }
    
    return size;
}

size_t sub(int *bytes1, int *bytes2, int *result, size_t size) {
    for (size_t i = 0; i < size; i++) {
        result[i] = bytes1[i] - bytes2[i];
    }
    
    return size;
}

size_t xor(const char *message, 
		   unsigned char *key_stream, 
		   unsigned char *result, 
		   size_t size){
	for (size_t i = 0; i < size; i++) {
		result[i] = message[i] ^ key_stream[i];
	}
	
	return size;
}

void swap(unsigned char *s, size_t i, size_t j) {
    unsigned char aux = s[i];
    s[i] = s[j];
    s[j] = aux;
}
