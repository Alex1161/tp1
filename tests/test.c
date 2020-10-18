#include <stdio.h>
#include "Test_encryptors/test_cesar.h"
#include "Test_encryptors/test_vigenere.h"
#include "Test_encryptors/test_arc4.h"

/*--------------------------------------
  --------------. Main -----------------
  --------------------------------------*/

int main() {
  printf("------------TEST CESAR------------\n");
	test_cesar();
  printf("-----------TEST VIGENERE----------\n");
  test_vigenere();
  printf("------------TEST ARC4-------------\n");
  test_arc4();
	return 0;
}