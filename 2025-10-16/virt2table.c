#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int highestBit(int64_t num) {
    int rc = 0;
    while (num != 0) {
        num >>= 1L;
        rc += 1;
    }
    return rc;
}

char *toBinary(int64_t num, char *buffer) {
    int high_bit = highestBit(num);
    for (int i = 0; i < high_bit; i++) {
        buffer[high_bit-i-1] = (num & (1L << i)) ? '1' : '0';
    }
    buffer[high_bit] = '\0';
    return buffer;
}

int main(int argc, char **argv) {
    char buffer[65];
    
    if (argc != 2) {
        printf("USAGE: %s page_size_in_K\n", argv[0]);
        exit(1);
    }

    int64_t page_size = strtol(argv[1], 0, 10) * 1024;
    int64_t offset_bits = highestBit(page_size) - 1;
    printf("page size %ld bytes %ld offset bits\n", page_size, offset_bits);

    int64_t addr = (int64_t)main;
    printf("main = %lx\n", addr);
    printf("main = %s\n", toBinary(addr, buffer));
    printf("offset = %lx\n", addr & ((1 << offset_bits) - 1));
    addr >>= 12; // shift past offset
    printf("p1 index = %lx\n", addr & 0b111111111);
    addr >>= 9; // shift past p1 index
    printf("p2 index = %lx\n", addr & 0b111111111);
    addr >>= 9; // shift past p2 index
    printf("p3 index = %lx\n", addr & 0b111111111);
    addr >>= 9; // shift past p3 index
    printf("p4 index = %lx\n", addr & 0b111111111);
    printf("p4 index = %s\n", toBinary(addr & 0b111111111, buffer));
}
