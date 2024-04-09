#include <stdio.h>
#include "DataStream.h"
#include "compression.h"

int main() {
    DataStream data_stream = create_datastream_from_file("example.bin");
    printf("Data size: %d\n", data_stream.size);

    Block block = get_block(&data_stream);
    print_block(block);

    CompressedHeader header = perform_compression(&block);
    print_compressed_header(header);

    print_block(block);
    return 0;
}