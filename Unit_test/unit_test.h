#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <stdbool.h>

typedef bool (*tester_callback_t)(void *element1, void *element2);
typedef void (*tester_print_t)(void *element);

typedef struct {
    tester_callback_t equals;
    tester_print_t print;
    const char *test_name;
} tester_t;


int tester_init(tester_t *self,
                tester_callback_t equals,
                tester_print_t print,
                const char *test_name);
int tester_uninit(tester_t *self);

void tester_test(tester_t *self, void *expected, void *actual);

#endif