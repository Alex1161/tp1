#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "common_processor.h"

const int METHOD_LENGTH = 9;
const int KEY_LENGTH = 6;

int main(int argc, char const *argv[]) {
    //Parseando los argumentos de comando de linea
    const char *server_host = argv[1];
    const char *server_port = argv[2];
    char method[strlen(argv[3]) - METHOD_LENGTH + 1];
    memset(method, 0, (strlen(argv[3]) - METHOD_LENGTH + 1) * sizeof(char));
    strncpy(method, 
            &argv[3][METHOD_LENGTH], 
            strlen(argv[3]) - METHOD_LENGTH + 1);
    char key[strlen(argv[4]) - KEY_LENGTH];
    strncpy(key, &argv[4][KEY_LENGTH], strlen(argv[4]) - KEY_LENGTH + 1);

    processor_t processor;
    processor_init(&processor, method, key);
    processor_process_client(&processor, server_host, server_port, NULL);
    processor_uninit(&processor);

    return 0;
}
