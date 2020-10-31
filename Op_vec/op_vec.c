#include "op_vec.h"
#include <string.h>
#include <stdlib.h>

char* itoa(int value, char* result, int base) {
	if (base < 2 || base > 36) { 
		*result = '\0'; return result; 
	}

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;
	do {
		tmp_value = value;
		value /= base;
		*ptr++ = 
		"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while (value);

	if (tmp_value < 0) *ptr++ = '-';
	
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}

	return result;
}

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

size_t un_char_to_hexa(unsigned char *element, 
					   char *hexa, 
					   size_t size_element) {
	int *bytes = malloc(size_element * sizeof(int));
	un_char_to_bytes(element, bytes, size_element);

	char aux[2] = "";
	itoa(bytes[0], aux, 16);
	strncpy(hexa, aux, 2);

	for (size_t i = 1; i < size_element; i++) {
		itoa(bytes[i], aux, 16);
		strncat(hexa, aux, 2);
	}
	
	free(bytes);
	return 2 * size_element;
}
