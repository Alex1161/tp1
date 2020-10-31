#include "common_file_processor.h"
#include <string.h>

const size_t CHUNK = 64;

/*---------------------------------------------------------------------------
  ------------------ AUXILIAR FUNCTIONS DECLARATIONS ------------------------
  ---------------------------------------------------------------------------*/

static size_t file_size(FILE *file);

/*---------------------------------------------------------------------------
  ------------------------- FUNCTIONS DEFINITIONS ---------------------------
  ---------------------------------------------------------------------------*/

int file_processor_reader_init(file_processor_t *self, 
                               const char *file_name) {
    self->name = file_name;
    self->file = (file_name == NULL) ? stdin : fopen(file_name, "r");
    if (! self->file) {
        return 1;
    }
    self->file_size = file_size(self->file);
    
    return 0;
}

int file_processor_writer_init(file_processor_t *self, 
                               const char *file_name) {
    self->name = file_name;
    self->file = (file_name == NULL) ? stdout : fopen(file_name, "w");
    if (! self->file) {
        return 1;
    }
    self->file_size = file_size(self->file);
    
    return 0;
}

size_t file_processor_read(file_processor_t *self, char *msg) {
    char buffer[CHUNK];
    memset(buffer, 0, CHUNK * sizeof(char));

    size_t size = file_size(self->file);

    while (! feof(self->file)) {
        size_t read = fread(buffer, 1, CHUNK, self->file);
        strncat(msg, buffer, read);
    }

    return size;
}

size_t file_processor_write(file_processor_t *self, 
                            char *buffer, 
                            size_t size_buffer) {
    return fwrite(buffer, 1, size_buffer, stdout);
}

int file_processor_uninit(file_processor_t *self) {
    if (self->name != NULL) {
        fclose(self->file);
    }

    return 0;
}

/*---------------------------------------------------------------------------
  ------------------ AUXILIAR FUNCTIONS DEFINITIONS -------------------------
  ---------------------------------------------------------------------------*/

static size_t file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);
    
    return file_size;
}
