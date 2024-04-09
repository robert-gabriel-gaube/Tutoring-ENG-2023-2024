#include "../include/generals.h"

void throw_error(const char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);

    exit(1);
}

void* safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        throw_error("Error: Could not allocate memory\n");
    }

    return ptr;
}

FILE* open_file(const char *filepath, const char *mode) {
    FILE *file = fopen(filepath, mode);
    if (file == NULL) {
        throw_error("Error: Could not open file %s\n", filepath);
    }

    return file;
}

size_t get_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    return size;
}
