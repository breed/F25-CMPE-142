#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (fork() == 0) {
        execlp("echo", "echo-no", "5309", NULL);
        exit(99);
    }
    int status;
    wait(&status);
    printf("all done exit code %d\n", WEXITSTATUS(status));
}
