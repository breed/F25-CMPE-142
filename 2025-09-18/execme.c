#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    execlp("echo", "echo", "hello world!", NULL);
    printf("all done\n");
}
