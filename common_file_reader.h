#ifndef __FILE_READER_H__
#define __FILE_READER_H__

#include <stddef.h>
#include <stdio.h>

typedef struct{
    const char *name;
    FILE *file;
    size_t file_size;
} file_reader_t;

int file_reader_init(file_reader_t *file_reader, const char *name);

// Lee todo el contenido del archivo y lo guarda en msg
// Devuelve el tamaño
size_t file_reader_read(file_reader_t *file_reader, char *msg);
int file_reader_uninit(file_reader_t *file_reader);

#endif
