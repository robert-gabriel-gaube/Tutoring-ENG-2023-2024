#include "compression.h"
#include <math.h>
#include <string.h>

void print_block(Block block) {
    for (int i = 0; i < 8; i++) {
        printf("%X ", block.data[i]);
    }
    printf("\n");
}

CompressedHeader create_header(Block *block) {
    uint8_t min = 0xFF, max = 0;

    for (int i = 0; i < 8; i++) {
        min = block->data[i] < min ? block->data[i] : min;
        max = block->data[i] > max ? block->data[i] : max;
    }

    uint8_t difference_size = log2(max - min) + 1;

    CompressedHeader header;
    if(difference_size == 8) {
        header.compression_type = UNCOMPRESSED;
        return header;
    }

    header.minimum = min;
    header.differences_size = difference_size;
    header.compression_type = COMPRESSED;

    return header;
}

void compress_block(CompressedHeader header, Block *block) {
    Block compressed_block;
    memset(compressed_block.data, 0, 8);
    print_block(compressed_block);

    for(int i = 0; i < 8; i++) {
        block->data[i] -= header.minimum;
    }
    size_t cursor = 0;
    for(int i = 0; i < 8; i++) {
        compressed_block.data[cursor / 8] |= block->data[i] << (cursor % 8);
        print_block(compressed_block);
        cursor += header.differences_size;
    }

    memcpy(block->data, compressed_block.data, 8);
}

CompressedHeader perform_compression(Block* block) {
    CompressedHeader header = create_header(block);
    if(header.compression_type == UNCOMPRESSED) {
        return header;
    }
    compress_block(header, block);
    return header;
}

void print_compressed_header(CompressedHeader header) {
    printf("Compression type: %d\n", header.compression_type);

    if(header.compression_type == COMPRESSED) {    
        printf("Minimum: %X\n", header.minimum);
        printf("Differences size: %d\n", header.differences_size);
    }
}