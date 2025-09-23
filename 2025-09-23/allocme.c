#include <stdio.h>
#include <stdlib.h>

void foo(int i) {
    char buffer[5000];
    for (int i = 0; i < 5000; i+=1000) {
        buffer[i] = (char)i;
    }
    char *ptr = malloc(5000);
    for (int i = 0; i < 5000; i+=1000) {
        ptr[i] = (char)i;
    }
    printf("%p %p\n", buffer, ptr);
    foo(i+1);
}

int main() {
    foo(0);
}
