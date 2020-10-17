#ifndef __VISITOR_H__
#define __VISITOR_H__

#include <stdbool.h>
#include <stddef.h>

char* itoa(int value, char* result, int base);
size_t un_char_to_hexa(unsigned char *element, char *hexa, size_t size_element);
size_t un_char_to_bytes(unsigned char *element, int *bytes, size_t size_element);
bool equals(void *s1, void *s2);
void print(void* element);

#endif