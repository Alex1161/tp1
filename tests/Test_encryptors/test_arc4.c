#include "test_arc4.h"
#include "../../Unit_test/unit_test.h"
#include "../../Encryptors/arc4.h"
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

/*--------------------------------------
  ------------- Test Cesar -------------
  --------------------------------------*/

void test_arc4(){
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}

/*--------------------------------------
  ------ Test Cases Definitions --------
  --------------------------------------*/

static void test1(){
    encryptor_arc4_t encryptor_arc4;
    encryptor_arc4_init(&encryptor_arc4, "queso", 5);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"encode Pan with key queso -> 69cae6");

    unsigned char encoded[3] = "";
	const char msg[] = "Pan";
    encryptor_arc4_encode(&encryptor_arc4, msg, strlen(msg), encoded);
	char actual[6] = "";
	un_char_to_hexa(encoded, actual, 3);
    const char expected[] = "69cae6";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_arc4_uninit(&encryptor_arc4);
}

static void test2(){
    encryptor_arc4_t encryptor_arc4;
    encryptor_arc4_init(&encryptor_arc4, "Key", 3);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"encode Plaintext with key Key -> bbf316e8d940afad3");

    unsigned char encoded[9] = "";
	const char msg[] = "Plaintext";
    encryptor_arc4_encode(&encryptor_arc4, msg, strlen(msg), encoded);
	char actual[18] = "";
	un_char_to_hexa(encoded, actual, 9);
    const char expected[] = "bbf316e8d940afad3";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_arc4_uninit(&encryptor_arc4);
}

static void test3(){
    encryptor_arc4_t encryptor_arc4;
    encryptor_arc4_init(&encryptor_arc4, "Clave de 128 bit", 16);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"encode Un saludo with key Clave de 128 bit -> e97b3273b466d491a1");

    unsigned char encoded[9] = "";
	const char msg[] = "Un saludo";
    encryptor_arc4_encode(&encryptor_arc4, msg, strlen(msg), encoded);
	char actual[18] = "";
	un_char_to_hexa(encoded, actual, 9);
    const char expected[] = "e97b3273b466d491a1";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_arc4_uninit(&encryptor_arc4);
}

static void test4(){
    encryptor_arc4_t encryptor_arc4;
    encryptor_arc4_init(&encryptor_arc4, "queso", 5);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"decode 69cae6 with key queso -> Pan");

    unsigned char encoded[3] = "";
	const char msg[] = "Pan";
    encryptor_arc4_encode(&encryptor_arc4, msg, strlen(msg), encoded);
	char actual[3] = "";
	encryptor_arc4_decode(&encryptor_arc4, encoded, 3, actual);
    const char expected[] = "Pan";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_arc4_uninit(&encryptor_arc4);
}

static void test5(){
    encryptor_arc4_t encryptor_arc4;
    encryptor_arc4_init(&encryptor_arc4, "Key", 3);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"decode bbf316e8d940afad3 with key Key -> Plaintext");

    unsigned char encoded[9] = "";
	const char msg[] = "Plaintext";
    encryptor_arc4_encode(&encryptor_arc4, msg, strlen(msg), encoded);
	char actual[9] = "";
	encryptor_arc4_decode(&encryptor_arc4, encoded, 9, actual);
    const char expected[] = "Plaintext";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_arc4_uninit(&encryptor_arc4);
}

static void test6(){
    encryptor_arc4_t encryptor_arc4;
    encryptor_arc4_init(&encryptor_arc4, "Clave de 128 bit", 16);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"decode e97b3273b466d491a1 with key Clave de 128 bit -> Un saludo");

    unsigned char encoded[9] = "";
	const char msg[] = "Un saludo";
    encryptor_arc4_encode(&encryptor_arc4, msg, strlen(msg), encoded);
	char actual[9] = "";
	encryptor_arc4_decode(&encryptor_arc4, encoded, 9, actual);
    const char expected[] = "Un saludo";

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_arc4_uninit(&encryptor_arc4);
}
