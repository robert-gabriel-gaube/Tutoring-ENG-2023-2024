#pragma once 
#include "generals.h"

#define BLOCK_SIZE 8

#define COMPRESSED 1 
#define UNCOMPRESSED 0

typedef struct {
    uint8_t data[BLOCK_SIZE];
}Block;

typedef struct {
    uint8_t compression_type : 1;
    uint8_t differences_size : 3;
    uint8_t minimum;
} __attribute__((packed)) CompressedHeader;

void print_block(Block block);
CompressedHeader perform_compression(Block* block);
void print_compressed_header(CompressedHeader header);
