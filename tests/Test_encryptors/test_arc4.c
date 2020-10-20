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
static void test7();

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
    test7();
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

static void test7(){
    encryptor_arc4_t encryptor_arc4;
    encryptor_arc4_init(&encryptor_arc4, "Secret", 6);

    tester_t test;
    tester_init(&test, 
				equals, 
				print, 
				"encode latin.txt with key Secret");

    unsigned char encoded[445] = "";
	const char msg[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    encryptor_arc4_encode(&encryptor_arc4, msg, strlen(msg), encoded);
	char actual[2 * 445] = "";
	un_char_to_hexa(encoded, actual, 445);
    const char expected_aux[] = "48bb19605188122932075d0a88f4d5fd\
4031a75c2d6f611a78bd357f2b199ef4\
961630196258400ea489c361ffc53cd3\
a9b85e86b3a2bf73ba3f158aca8040f2\
87a2abb132d15108e83eeaa830e512bd\
000f82eac44fc25e4b4de688c6ad422c\
a18f8ca41160cff6595aaa1722ec8ee9\
78b9b2d470a0310c36a27e967e4192cd\
6dc430b4162d88359e5e2623d5d3c923\
c5de88f8a2eb2ab8614d2c25c95a2dd7\
9e68a3f1c5f783a32bd7a2be9876e4a5\
d9adaaccc4ada775d581172cef4216c6\
8971400a5c58f7522b041830b3e73d69\
d2f9b85f4c42850cadf4f165a2cb29ad\
4b6798c0d017487951518d939e63af33\
c7dd9b435a2140ceabc79caf8f29bd97\
689c4c3c46c29dfe5113ca0e3baf678b\
b807f0d81e52dc15c508e10866687259\
de88fbfb561b3ca02664d5ce5223c39c\
7523de20fc6b34c2c334172dfd7b3715\
cedf09ee870c3f537f87ff2b5e795e22\
d0e1f5aa06ac3504afde1bd02825cbab\
114bd46794f7d919c1faf9c08333ca84\
46552fb7bbc65997db81034c1bcc5e0e\
0846abaf741a78fcf6653db7c4363629\
98909e32392ee002a13e58be99800f2c\
ebcc9978ae422fa55fea192a0f9793c9\
9ea5fed2d2780817391494b762";

    char expected[2 * 445] = "";
    for (size_t i = 0; i < 2 * 445; i+=2) {
        if (expected_aux[i] == '0') {
            strncat(expected, &expected_aux[i + 1], 1);
        }else{
            strncat(expected, &expected_aux[i], 2);
        }
    }

    tester_test(&test, (void *)expected, (void *)actual);

    tester_uninit(&test);
    encryptor_arc4_uninit(&encryptor_arc4);
}