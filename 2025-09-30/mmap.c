#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

struct hdr {
    int count1;
    int count2;
    char str[0];
};

int main(int argc, char **argv) {
    struct hdr *buffer = malloc(65536);
    printf("%ld %ld\n", sizeof buffer, sizeof *buffer);
    int fd = open(argv[1], O_RDWR);
    read(fd, buffer, 65536);
    // bufmap = mmap(NULL, 65536, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    while(1) {
        printf("buffer %x %x %s\n", buffer->count1, buffer->count2, buffer->str);
        printf("------\n");
        buffer->count1+=1;
        sleep(1);
    }
}
