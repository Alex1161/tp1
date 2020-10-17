#include <stdio.h>
#include "Test_encryptors/test_cesar.h"
#include "Test_encryptors/test_vigenere.h"


/*--------------------------------------
  --------------. Main -----------------
  --------------------------------------*/

int main() {
  printf("\tTest cesar\n");
	test_cesar();
  printf("\tTest vigenere\n");
  test_vigenere();
	return 0;
}