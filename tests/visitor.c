#include "visitor.h"
#include <stdio.h>
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

bool equals(void *s1, void *s2) {
	size_t size = strlen((char *)s1);
	return (strncmp((char *)s1, (char *)s2, size) == 0) ? true : false;
}

void print(void* element){
	printf("%s", (char *)element);
}