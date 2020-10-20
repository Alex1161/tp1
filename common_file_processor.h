#ifndef __FILE_PROCESSOR_H__
#define __FILE_PROCESSOR_H__

#include <stddef.h>
#include <stdio.h>

typedef struct{
    const char *name;
    FILE *file;
    size_t file_size;
} file_processor_t;

int file_processor_reader_init(file_processor_t *self, 
                               const char *file_name);

int file_processor_writer_init(file_processor_t *self, 
                               const char *file_name);

// Lee todo el contenido del archivo y lo guarda en msg. Devuelve el tamaño
size_t file_processor_read(file_processor_t *self, char *msg);

// Escribe todo el buffer en el archivo y devuelve el tamaño
size_t file_processor_write(file_processor_t *self, 
                            char *buffer, 
                            size_t size_buffer);
int file_processor_uninit(file_processor_t *self);

#endif
