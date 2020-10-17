#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <stdbool.h>

// Funcion adaptadora para comparar los elementos
typedef bool (*tester_callback_t)(void *element1, void *element2);

// Funcion adaptadora para imprimir los elementos
typedef void (*tester_print_t)(void *element);

typedef struct {
    tester_callback_t equals;
    tester_print_t print;
    const char *test_name;
} tester_t;

// Constructor y destructor
int tester_init(tester_t *self,
                tester_callback_t equals,
                tester_print_t print,
                const char *test_name);
int tester_uninit(tester_t *self);

// Testeo
void tester_test(tester_t *self, void *expected, void *actual);

#endif