#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "../Unit_test/unit_test.h"
#include "../Encryptors/cesar.h"

/*--------------------------------------
  ------ Test Cases Declarations -------
  --------------------------------------*/
void test1();

/*--------------------------------------
  --------------. Main -----------------
  --------------------------------------*/
static bool equals(void *s1, void *s2);
static void print(void* element);

int main(int argc, char const *argv[]) {
  test1();
  return 0;
}

static bool equals(void *s1, void *s2) {
  return (strcmp((char *)s1, (char *)s2) == 0) ? true : false;
}

static void print(void* element){
  printf("%s\n", (char *)element);
}

/*--------------------------------------
  ------ Test Cases Definitions -------
  --------------------------------------*/
void test1(){
  encryptor_cesar_t encryptor_cesar;
  encryptor_cesar_init(&encryptor_cesar, 5);

  tester_t test1;
  tester_init(&test1, equals, print, "Pan -> 7BI");

  const char actual[10];
  encode(&encryptor_cesar, "Pan", actual);
  const char expected[] = "7BI";

  tester_test(&test1, (void *)expected, (void *)actual);

  tester_uninit(&test1);
  encryptor_cesar_uninit(&encryptor_cesar);
}
