#include "common_processor.h"
#include "common_file_reader.h"
#include "common_socket.h"
#include "common_encryptor.h"
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------------
  ------------------ AUXILIAR FUNCTIONS DECLARATIONS ------------------------
  ---------------------------------------------------------------------------*/

static void connect_send(processor_t *self, 
                         const char *server_host, 
                         const char *server_port, 
                         char *msg, 
                         size_t msg_length);

/*---------------------------------------------------------------------------
  ------------------------- FUNCTIONS DEFINITIONS ---------------------------
  ---------------------------------------------------------------------------*/

int processor_init(processor_t *self, char *method, char *key) {
    self->method = method;
    self->key = key;

    return 0;
}

int processor_process(processor_t *self, 
                      const char *server_host, 
                      const char *server_port) {
    file_reader_t file_reader;
    file_reader_init(&file_reader, NULL);
    char *msg = malloc((file_reader.file_size + 1) * sizeof(char));
    memset(msg, 0, (file_reader.file_size) * sizeof(char));
    size_t read = file_reader_read(&file_reader, msg);
    file_reader_uninit(&file_reader);

    connect_send(self, server_host, server_port, msg, read);

    free(msg);
    return 0;
}

int processor_uninit(processor_t *self) {
    // Do nothing
    return 0;
}

/*---------------------------------------------------------------------------
  ------------------ AUXILIAR FUNCTIONS DEFINITIONS -------------------------
  ---------------------------------------------------------------------------*/

static void connect_send(processor_t *self, 
                         const char *server_host, 
                         const char *server_port, 
                         char *msg, 
                         size_t msg_length){
    socket_t socket;
    encryptor_t encryptor;

    socket_init(&socket);
    unsigned char *result = malloc(msg_length * sizeof(unsigned char));
    encryptor_init(&encryptor, self->method, self->key);

    socket_connect(&socket, server_host, server_port);
    encryptor_encode(&encryptor, msg, msg_length, result);
    socket_send(&socket, (const char *)result, msg_length);
    
    encryptor_uninit(&encryptor);
    free(result);
    socket_uninit(&socket);
}
