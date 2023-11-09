#include "../problem1.c"
#include <assert.h>

int main() {
    unsigned number = 0x76543210;
    
    for(int idx = 0; idx < sizeof(number) * 2; ++idx) {
        assert(idx == get_nibble(number, idx));
    }
    return 0;
}