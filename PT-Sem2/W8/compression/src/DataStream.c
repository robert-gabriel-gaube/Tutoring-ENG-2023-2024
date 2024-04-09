#include "DataStream.h"
#include "generals.h"
#include <stdlib.h>
#include <string.h>

DataStream create_datastream_from_file(const char *filepath) {
    DataStream data_stream;

    FILE *file = open_file(filepath, "rb");
    size_t file_size = get_file_size(file);

    data_stream.data = safe_malloc(file_size);
    fread(data_stream.data, 1, file_size, file);

    data_stream.size = file_size * 8; // in bits
    data_stream.cursor = 0;

    fclose(file);
    return data_stream;
}

DataStream create_empty_datastream() {
    DataStream data_stream;
    data_stream.data = NULL;
    data_stream.size = 0;
    data_stream.cursor = 0;

    return data_stream;
}

Block get_block(DataStream* data_stream) {
    Block block;

    if (data_stream->cursor + 64 > data_stream->size) {
        throw_error("Cursor is out of bounds\n");
    }

    memcpy(block.data, data_stream->data + data_stream->cursor, 8);
    data_stream->cursor += 64;
    
    return block;
}

void delete_datastream(DataStream data_stream) {
    free(data_stream.data);
}