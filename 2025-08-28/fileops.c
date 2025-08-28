#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct s {
    int i;
    int j;
};

int main() {
    struct s mys = { 1,2};
    struct s *pmys = &mys;
    int myi = (*pmys).i;
    int myotheri = pmys->i;

    char *chars = "1234";
    char c = chars[1];
    //char c = *(chars+1)
    //char c = *(1+chars)
    //char c = 1[chars];

    int i = 0x006e6562;
    char *ptr = (char*)&i;
    printf("%s\n", ptr);
    int rc = write(4, "hello!\n", 7);
    if (rc == -1) {
        perror("problem with 4");
    }
    exit(2);
}
