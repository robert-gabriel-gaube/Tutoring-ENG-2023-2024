#pragma once
#include <stdint.h>
#include "compression.h"

typedef struct {
    uint8_t* data;
    uint32_t size;
    uint32_t cursor;
}DataStream; 

DataStream create_datastream_from_file(const char *filepath);
DataStream create_empty_datastream();
void delete_datastream(DataStream data_stream);
Block get_block(DataStream* data_stream);
