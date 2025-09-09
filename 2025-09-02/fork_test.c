#include <stdio.h>
#include <unistd.h>

int main() {
    printf("hello world! i am %d\n", getpid());
    int i = 0;
    pid_t pid = fork();
    if (pid == 0) {
        i += 3;
    } else {
        i++;
    }
    printf("my id %d hello again! %d %d\n", getpid(), pid, i);
}

