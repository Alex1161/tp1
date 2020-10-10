#include "visitor.h"
#include <stdio.h>
#include <string.h>

bool equals(void *s1, void *s2) {
  return (strcmp((char *)s1, (char *)s2) == 0) ? true : false;
}

void print(void* element){
  printf("%s\n", (char *)element);
}