#include "test_cesar.h"
#include "../../Unit_test/unit_test.h"
#include "../../Encryptors/cesar.h"
#include "../../Op_vec/op_vec.h"
#include "Adapters/adapters.h"
#include <string.h>

/*--------------------------------------
  ------ Test Cases Declarations -------
  --------------------------------------*/
  
static void test1();
static void test2();
static void test3();

/*--------------------------------------
  ------------- Test Cesar -------------
  --------------------------------------*/

void test_cesar(){
    test1();
	test2();
	test3();
}

/*--------------------------------------
  ------ Test Cases Definitions --------
  --------------------------------------*/

static void test1(){
    encryptor_cesar_t encryptor_cesar;
    encryptor_cesar_init(&encryptor_cesar, 5);

    tester_t test1;
    tester_init(&test1, equals, print, "encode Pan -> 556673");

    unsigned char encoded[3] = "";
    encryptor_cesar_encode(&encryptor_cesar, "Pan", 3, encoded);
	char actual[6] = "";
	un_char_to_hexa(encoded, actual, 3);
    const char expected[] = "556673";

    tester_test(&test1, (void *)expected, (void *)actual);

    tester_uninit(&test1);
    encryptor_cesar_uninit(&encryptor_cesar);
}

static void test2(){
	encryptor_cesar_t encryptor_cesar;
	encryptor_cesar_init(&encryptor_cesar, 5);

	tester_t test2;
	tester_init(&test2, equals, print, "decode 556673 -> Pan");

	char actual[3] = "";
	encryptor_cesar_decode(&encryptor_cesar, (unsigned char *)"Ufs", 3, actual);
	const char expected[] = "Pan";

	tester_test(&test2, (void *)expected, (void *)actual);

	tester_uninit(&test2);
	encryptor_cesar_uninit(&encryptor_cesar);
}

static void test3(){
	encryptor_cesar_t encryptor_cesar;
	encryptor_cesar_init(&encryptor_cesar, 191);

	tester_t test3;
	tester_init(&test3, equals, print, "encode BABA -> 1010");

	unsigned char encoded[4] = "";
    encryptor_cesar_encode(&encryptor_cesar, "BABA", 4, encoded);
	char actual[8] = "";
	un_char_to_hexa(encoded, actual, 4);
    const char expected[] = "1010";

	tester_test(&test3, (void *)expected, (void *)actual);

	tester_uninit(&test3);
	encryptor_cesar_uninit(&encryptor_cesar);
}

