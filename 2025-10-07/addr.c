#include <stdio.h>
#include <stdlib.h>

void foo() {
        int i;
        char *p = malloc(300);
        printf("foo@%p i@%p p@%p\n", foo, &i, p);
}

int main() {
        foo();
}
