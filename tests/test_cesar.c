#include "test_cesar.h"
#include "unit_test.h"
#include "cesar.h"
#include "visitor.h"
#include <stdlib.h>

/*--------------------------------------
  ------ Test Cases Declarations -------
  --------------------------------------*/
  
static void test1();
static void test2();

/*--------------------------------------
  ------------- Test Cesar -------------
  --------------------------------------*/

void test_cesar(){
    test1();
	test2();
}

/*--------------------------------------
  ------ Test Cases Definitions --------
  --------------------------------------*/

static void test1(){
    encryptor_cesar_t encryptor_cesar;
    encryptor_cesar_init(&encryptor_cesar, 5);

    tester_t test1;
    tester_init(&test1, equals, print, "encode Pan -> Ufs");

	//char actual[3]; por que no funciona???
    unsigned char *actual = malloc(3 * sizeof(unsigned char));
    encode(&encryptor_cesar, "Pan", 3, actual);
    const char expected[] = "Ufs";
    tester_test(&test1, (void *)expected, (void *)actual);

	free(actual);
    tester_uninit(&test1);
    encryptor_cesar_uninit(&encryptor_cesar);
}

static void test2(){
	encryptor_cesar_t encryptor_cesar;
	encryptor_cesar_init(&encryptor_cesar, 5);

	tester_t test2;
	tester_init(&test2, equals, print, "decode Ufs -> Pan");

	char *actual = malloc(3 * sizeof(char));
	decode(&encryptor_cesar, "Ufs", 3, actual);
	const char expected[] = "Pan";

	tester_test(&test2, (void *)expected, (void *)actual);

	free(actual);
	tester_uninit(&test2);
	encryptor_cesar_uninit(&encryptor_cesar);
}
