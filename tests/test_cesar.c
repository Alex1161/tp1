#include "test_cesar.h"
#include "../Unit_test/unit_test.h"
#include "../Encryptors/cesar.h"
#include "visitor.h"

/*--------------------------------------
  ------ Test Cases Declarations -------
  --------------------------------------*/
  
static void test1();

/*--------------------------------------
  ------------- Test Cesar -------------
  --------------------------------------*/

void test_cesar(){
    test1();
}

/*--------------------------------------
  ------ Test Cases Definitions --------
  --------------------------------------*/

static void test1(){
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

// static void test2(){
//   encryptor_cesar_t encryptor_cesar;
//   encryptor_cesar_init(&encryptor_cesar, 5);

//   tester_t test1;
//   tester_init(&test1, equals, print, "Pan -> 7BI");

//   const char actual[10];
//   encode(&encryptor_cesar, "Pan", actual);
//   const char expected[] = "7BI";

//   tester_test(&test1, (void *)expected, (void *)actual);

//   tester_uninit(&test1);
//   encryptor_cesar_uninit(&encryptor_cesar);
// }

