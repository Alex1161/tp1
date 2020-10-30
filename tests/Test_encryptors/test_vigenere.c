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
static void test4();
static void test5();
static void test6();
static void test7();
static void test8();

/*--------------------------------------
  ------------- Test Cesar -------------
  --------------------------------------*/

void test_vigenere(){
    test1();
	test2();
	test3();
    test4();
    test5();
    test6();
    test7();
    test8();
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
    encryptor_vigenere_encode(&encryptor_vigenere, msg, strlen(msg), encoded, 0);
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
    encryptor_vigenere_encode(&encryptor_vigenere, msg, strlen(msg), encoded, 0);
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
    encryptor_vigenere_encode(&encryptor_vigenere, msg, strlen(msg), encoded, 0);
	char actual[4] = "";
	un_char_to_hexa(encoded, actual, 2);
    const char expected[] = "deec";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_vigenere_uninit(&encryptor_vigenere);
}

static void test4(){
	encryptor_vigenere_t encryptor_vigenere;
    encryptor_vigenere_init(&encryptor_vigenere, "y", 1);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"decode deec es with key y -> es");

    unsigned char encoded[2] = "";
	const char msg[] = "es";
    encryptor_vigenere_encode(&encryptor_vigenere, msg, strlen(msg), encoded, 0);
	char actual[2] = "";
    encryptor_vigenere_decode(&encryptor_vigenere, encoded, 2, actual, 0);
    const char expected[] = "es";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_vigenere_uninit(&encryptor_vigenere);
}

static void test5(){
	encryptor_vigenere_t encryptor_vigenere;
    encryptor_vigenere_init(&encryptor_vigenere, "yS", 2);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"decode dec6 with key yS-> es");

    unsigned char encoded[2] = "";
	const char msg[] = "es";
    encryptor_vigenere_encode(&encryptor_vigenere, msg, strlen(msg), encoded, 0);
	char actual[2] = "";
    encryptor_vigenere_decode(&encryptor_vigenere, encoded, 2, actual, 0);
    const char expected[] = "es";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_vigenere_uninit(&encryptor_vigenere);
}

static void test6(){
    encryptor_vigenere_t encryptor_vigenere;
    encryptor_vigenere_init(&encryptor_vigenere, "SecureKey", 9);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"decode a6cac6e7d7d96bd2dec6d8c4dcd7 with key SecureKey -> Secret message");

    unsigned char encoded[14] = "";
	const char msg[] = "Secret message";
    encryptor_vigenere_encode(&encryptor_vigenere, msg, strlen(msg), encoded, 0);
	char actual[14] = "";
	encryptor_vigenere_decode(&encryptor_vigenere, encoded, 14, actual, 0);
    const char expected[] = "Secret message";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_vigenere_uninit(&encryptor_vigenere);
}

static void test7(){
    encryptor_vigenere_t encryptor_vigenere;
    encryptor_vigenere_init(&encryptor_vigenere, "SecureKey", 9);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"encode Secret message with key SecureKey in 2 parts -> a6cac6e7d7d96bd2dec6d8c4dcd7");

    unsigned char encoded1[6] = "";
	const char msg1[] = "Secret";
    encryptor_vigenere_encode(&encryptor_vigenere, msg1, strlen(msg1), encoded1, 0);
	char actual1[12] = "";
	un_char_to_hexa(encoded1, actual1, 6);
    const char expected1[] = "a6cac6e7d7d9";

    tester_test(&test, (void *)expected1, (void *)actual1);

    unsigned char encoded2[8] = "";
	const char msg2[] = " message";
    encryptor_vigenere_encode(&encryptor_vigenere, msg2, strlen(msg2), encoded2, 6);
	char actual2[16] = "";
	un_char_to_hexa(encoded2, actual2, 8);
    const char expected2[] = "6bd2dec6d8c4dcd7";

    tester_test(&test, (void *)expected2, (void *)actual2);

    tester_uninit(&test);
    encryptor_vigenere_uninit(&encryptor_vigenere);
}

static void test8(){
    encryptor_vigenere_t encryptor_vigenere;
    encryptor_vigenere_init(&encryptor_vigenere, "SecureKey", 9);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"decode a6cac6e7d7d96bd2dec6d8c4dcd7 with key SecureKey in 2 parts-> Secret message");

    unsigned char encoded1[6] = "";
	const char msg1[] = "Secret";
    encryptor_vigenere_encode(&encryptor_vigenere, msg1, strlen(msg1), encoded1, 0);
	char actual1[6] = "";
	encryptor_vigenere_decode(&encryptor_vigenere, encoded1, 6, actual1, 0);
    const char expected1[] = "Secret";

    tester_test(&test, (void *)expected1, (void *)actual1);

    unsigned char encoded2[8] = "";
	const char msg2[] = " message";
    encryptor_vigenere_encode(&encryptor_vigenere, msg2, strlen(msg2), encoded2, 6);
	char actual2[8] = "";
	encryptor_vigenere_decode(&encryptor_vigenere, encoded2, 8, actual2, 6);
    const char expected2[] = " message";

    tester_test(&test, (void *)expected2, (void *)actual2);

    tester_uninit(&test);
    encryptor_vigenere_uninit(&encryptor_vigenere);
}
