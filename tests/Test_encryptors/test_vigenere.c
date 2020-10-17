#include "test_vigenere.h"
#include "../../Unit_test/unit_test.h"
#include "../../Encryptors/vigenere.h"
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

void test_vigenere(){
    test1();
	test2();
	test3();
}

/*--------------------------------------
  ------ Test Cases Definitions --------
  --------------------------------------*/

static void test1(){
    encryptor_vigenere_t encryptor_vigenere;
    encryptor_vigenere_init(&encryptor_vigenere, "SecureKey", 9);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"encode Secret message with key SecureKey-> a6cac6e7d7d96bd2dec6d8c4dcd7");

    unsigned char encoded[14] = "";
	const char msg[] = "Secret message";
    encryptor_vigenere_encode(&encryptor_vigenere, msg, strlen(msg), encoded);
	char actual[28] = "";
	un_char_to_hexa(encoded, actual, 14);
    const char expected[] = "a6cac6e7d7d96bd2dec6d8c4dcd7";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_vigenere_uninit(&encryptor_vigenere);
}

static void test2(){
	encryptor_vigenere_t encryptor_vigenere;
    encryptor_vigenere_init(&encryptor_vigenere, "yS", 2);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"encode es with key yS-> dec6");

    unsigned char encoded[2] = "";
	const char msg[] = "es";
    encryptor_vigenere_encode(&encryptor_vigenere, msg, strlen(msg), encoded);
	char actual[4] = "";
	un_char_to_hexa(encoded, actual, 2);
    const char expected[] = "dec6";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_vigenere_uninit(&encryptor_vigenere);
}

static void test3(){
	encryptor_vigenere_t encryptor_vigenere;
    encryptor_vigenere_init(&encryptor_vigenere, "y", 1);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"encode es with key y -> deec");

    unsigned char encoded[2] = "";
	const char msg[] = "es";
    encryptor_vigenere_encode(&encryptor_vigenere, msg, strlen(msg), encoded);
	char actual[4] = "";
	un_char_to_hexa(encoded, actual, 2);
    const char expected[] = "deec";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_vigenere_uninit(&encryptor_vigenere);
}
