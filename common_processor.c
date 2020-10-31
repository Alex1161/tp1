#include "common_processor.h"
#include "common_socket.h"
#include "common_encryptor.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const size_t CHUNK_SIZE = 64;

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
    //Socket
    socket_t socket;
    socket_init(&socket);
    socket_connect(&socket, server_host, server_port);

    //op archivos
    FILE *file = (file_name == NULL) ? stdin : fopen(file_name, "r");
    if (! file) {
        return 1;
    }

    char msg[CHUNK_SIZE];
    memset(msg, 0, CHUNK_SIZE * sizeof(char));
    while (! feof(file)) {
        size_t read = fread(msg, 1, CHUNK_SIZE, file);
        
        unsigned char result[CHUNK_SIZE];
        memset(result, 0, CHUNK_SIZE * sizeof(char));
    
        encryptor_encode(self->encryptor, msg, read, result);
        socket_send(&socket, (const char *)result, read);
    }

    if (file_name != NULL) {
        fclose(file);
    }

    socket_uninit(&socket);
    return 0;
}

int processor_process_server(processor_t *self, 
							 const char *server_port, 
							 const char *file_name) {
    socket_t socket;
    socket_init(&socket);
    socket_bind_listen(&socket, server_port);

    socket_t peer;
    socket_init(&peer);
    socket_accept(&socket, &peer);

    FILE *file = (file_name == NULL) ? stdout : fopen(file_name, "w");
    if (! file) {
        return 1;
    }

    char buffer[CHUNK_SIZE];
    memset(buffer, 0, CHUNK_SIZE * sizeof(char));
	int receive = socket_receive(&peer, buffer, CHUNK_SIZE);
    while (receive != 0){
        char result[CHUNK_SIZE];
        memset(result, 0, CHUNK_SIZE * sizeof(char));

        encryptor_decode(self->encryptor, buffer, receive, result);

        fwrite(result, 1, receive, file);
        receive = socket_receive(&peer, 
                                 buffer, 
                                 (int)CHUNK_SIZE);
        if(receive == -1){
            return 1;
        }
    }

    if (file_name != NULL) {
        fclose(file);
    }

    socket_uninit(&peer);
    socket_uninit(&socket);
	return 0;
}

int processor_uninit(processor_t *self) {
    encryptor_uninit(self->encryptor);
	free(self->encryptor);
    return 0;
}
