#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "common_encryptor.h"

typedef struct {
    encryptor_t *encryptor;
} processor_t;

int processor_init(processor_t *self, 
                   char *method, 
                   char *key);
int processor_process_client(processor_t *self, 
                      const char *server_host, 
                      const char *server_port,
                      const char *file_name);
int processor_process_server(processor_t *self, 
                             const char *server_port,
                             const char *file_name);
int processor_uninit(processor_t *self);

#endif
