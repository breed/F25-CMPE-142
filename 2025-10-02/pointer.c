#include <stdio.h>

struct hi {
    int i;
    char hi[5];
};

int main() {
    struct hi *p = (struct hi *)3;
    printf("%p\n", p);
    printf("%p\n", p+1);
    printf("%p\n", &p[1]);

}
