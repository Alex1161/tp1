#include "common_processor.h"
#include "common_file_processor.h"
#include "common_socket.h"
#include "common_encryptor.h"
#include <stdlib.h>
#include <string.h>

const size_t MAX_LENGTH = 1000;

/*---------------------------------------------------------------------------
  ------------------ AUXILIAR FUNCTIONS DECLARATIONS ------------------------
  ---------------------------------------------------------------------------*/

static void connect_send(encryptor_t *encryptor, 
                         const char *server_host, 
                         const char *server_port, 
                         char *msg, 
                         size_t msg_length);

static int connect_receive(encryptor_t *encryptor, 
						   const char *server_port, 
						   char *result, 
						   size_t max_result_length);

/*---------------------------------------------------------------------------
  ------------------------- FUNCTIONS DEFINITIONS ---------------------------
  ---------------------------------------------------------------------------*/

int processor_init(processor_t *self, char *method, char *key) {
	self->encryptor = malloc(sizeof(encryptor_t));
    encryptor_init(self->encryptor, method, key);

    return 0;
}

int processor_process_client(processor_t *self, 
                      const char *server_host, 
                      const char *server_port,
					  const char *file_name) {
    file_processor_t file_processor;
    file_processor_reader_init(&file_processor, file_name);
    char *msg = malloc((file_processor.file_size + 1) * sizeof(char));
    memset(msg, 0, (file_processor.file_size) * sizeof(char));
    size_t read = file_processor_read(&file_processor, msg);
    file_processor_uninit(&file_processor);

    connect_send(self->encryptor, server_host, server_port, msg, read);

    free(msg);
    return 0;
}

int processor_process_server(processor_t *self, 
							 const char *server_port, 
							 const char *file_name) {
    char buffer[MAX_LENGTH];
    memset(buffer, 0, MAX_LENGTH * sizeof(char));

	int received = connect_receive(self->encryptor, 
								   server_port, 
								   buffer, 
								   MAX_LENGTH);
    
    char *result = malloc(received * sizeof(char));
    memset(result, 0, received * sizeof(char));
    
	file_processor_t file_processor;
	file_processor_writer_init(&file_processor, NULL);

    encryptor_decode(self->encryptor, buffer, received, result);
	file_processor_write(&file_processor, result, received);

	file_processor_uninit(&file_processor);
    free(result);

	return 0;
}

int processor_uninit(processor_t *self) {
    encryptor_uninit(self->encryptor);
	free(self->encryptor);
    return 0;
}

/*---------------------------------------------------------------------------
  ------------------ AUXILIAR FUNCTIONS DEFINITIONS -------------------------
  ---------------------------------------------------------------------------*/

static void connect_send(encryptor_t *encryptor, 
                         const char *server_host, 
                         const char *server_port, 
                         char *msg, 
                         size_t msg_length){
    socket_t socket;
    socket_init(&socket);
    unsigned char *result = malloc(msg_length * sizeof(unsigned char));

    socket_connect(&socket, server_host, server_port);
    encryptor_encode(encryptor, msg, msg_length, result);
    socket_send(&socket, (const char *)result, msg_length);
    
    free(result);
    socket_uninit(&socket);
}

static int connect_receive(encryptor_t *encryptor, 
						   const char *server_port, 
						   char *result, 
						   size_t max_result_length) {
	socket_t socket;
    socket_init(&socket);
    socket_bind_listen(&socket, server_port);

    socket_t peer;
    socket_init(&peer);
    socket_accept(&socket, &peer);

	int receive = socket_receive(&peer, result, max_result_length);

    socket_uninit(&peer);
    socket_uninit(&socket);

	return receive;
}
