#include "unit_test.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int tester_init(tester_t *self,
                tester_callback_t equals,
                tester_print_t print,
                const char *test_name) {
    self->test_name = test_name;
    self->equals = equals;
    self->print = print;

    return 0;
}

void tester_test(tester_t *self, void *expected, void *actual) {
    bool passed = self->equals(expected, actual);

    if (passed) {
        printf("\033[0;32m");
        printf("Test %s: PASSED\n", self->test_name);
        printf("\033[0m");
    } else {
        printf("\033[1;31m");
        printf("Test %s: ERROR\n", self->test_name);
        printf("\tExpected: ");
        self->print(expected);
        printf("\n");
        printf("\tActual: ");
        self->print(actual);
        printf("\n");
        printf("\033[0m");
    }
}

int tester_uninit(tester_t *self){
    //Do nothing
    return 0;
}