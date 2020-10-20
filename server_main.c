#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "common_processor.h"

const int METHOD_LENGTH = 9;
const int KEY_LENGTH = 6;

int main(int argc, char const *argv[]) {
    //Parseando los argumentos de comando de linea
    const char *server_port = argv[1];
    char method[strlen(argv[2]) - METHOD_LENGTH];
    strncpy(method, 
            &argv[2][METHOD_LENGTH], 
            strlen(argv[2]) - METHOD_LENGTH + 1);
    char key[strlen(argv[3]) - KEY_LENGTH];
    strncpy(key, &argv[3][KEY_LENGTH], strlen(argv[3]) - KEY_LENGTH + 1);

    processor_t processor;
    processor_init(&processor, method, key);

    processor_process_server(&processor, server_port, NULL);

    processor_uninit(&processor);
    return 0;
}
