#include "op_vec.h"
#include <string.h>

char* itoa(int value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { 
		*result = '\0'; return result; 
	}

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;
	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while (value);

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}

	return result;
}

size_t un_char_to_bytes(unsigned char *element, int *bytes, size_t size_element) {
	size_t size = 0;
	for (size = 0; size < size_element; size++) {
		bytes[size] = (int) element[size];
	}
	
	return size;
}

size_t un_char_to_hexa(unsigned char *element, char *hexa, size_t size_element) {
	
	int bytes[size_element];
	un_char_to_bytes(element, bytes, size_element);

	char aux[2] = "";
	itoa(bytes[0], aux, 16);
	strcpy(hexa, aux);

	for (size_t i = 1; i < size_element; i++) {
		itoa(bytes[i], aux, 16);
		strncat(hexa, aux, 2);
	}
	
	return 2 * size_element;
}

// aun se puede factorizar
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
            bytes_key_aligned[i] = bytes_key[i - size_bytes_key];
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

size_t bytes_to_un_char(int *bytes, unsigned char *result, size_t size_bytes) {
    size_t size = 0;
	for (size = 0; size < size_bytes; size++) {
		result[size] = (unsigned char) bytes[size];
	}
	
	return size;
}
