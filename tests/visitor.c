#include "visitor.h"
#include <stdio.h>
#include <string.h>

bool equals(void *s1, void *s2) {
  size_t size = strlen((char *)s1);
  return (strncmp((char *)s1, (char *)s2, size) == 0) ? true : false;
}

void print(void* element){
  printf("%s", (char *)element);
}