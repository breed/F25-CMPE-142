#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (fork() == 0) {
        execlp("./testing.sh", "super-test", "5309", NULL);
        exit(99);
    }
    int status;
    wait(&status);
    printf("all done exit code %d\n", WEXITSTATUS(status));
}
