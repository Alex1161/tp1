#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

typedef struct {
    char *method;
    char *key;
} processor_t;

int processor_init(processor_t *self, char *method, char *key);
int processor_process(processor_t *self, 
                      const char *server_host, 
                      const char *server_port);
int processor_uninit(processor_t *self);

#endif
