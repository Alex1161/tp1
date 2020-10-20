#include "common_file_reader.h"
#include <string.h>

const size_t CHUNK_SIZE = 64;

/*---------------------------------------------------------------------------
  ------------------ AUXILIAR FUNCTIONS DECLARATIONS ------------------------
  ---------------------------------------------------------------------------*/

static size_t file_size(FILE *file);

/*---------------------------------------------------------------------------
  ------------------------- FUNCTIONS DEFINITIONS ---------------------------
  ---------------------------------------------------------------------------*/

int file_reader_init(file_reader_t *file_reader, const char *name) {
    file_reader->name = name;
    file_reader->file = (name == NULL) ? stdin : fopen(name, "rw");
    if (! file_reader->file) {
        return 1;
    }
    file_reader->file_size = file_size(file_reader->file);
    
    return 0;
}

size_t file_reader_read(file_reader_t *file_reader, char *msg){
    char buffer[CHUNK_SIZE];
    memset(buffer, 0, CHUNK_SIZE * sizeof(char));

    size_t size = file_size(file_reader->file);

    while (! feof(file_reader->file)) {
        size_t read = fread(buffer, 1, CHUNK_SIZE, file_reader->file);
        strncat(msg, buffer, read);
    }

    return size;
}

int file_reader_uninit(file_reader_t *file_reader) {
    if (file_reader->name != NULL) {
        fclose(file_reader->file);
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
