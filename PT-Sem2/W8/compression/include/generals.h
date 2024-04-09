#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>

void throw_error(const char* msg, ...);
void* safe_malloc(size_t size);
FILE* open_file(const char *filepath, const char *mode);
size_t get_file_size(FILE *file);
