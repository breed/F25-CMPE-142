#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main() {
    char message_to_child[1024];
    char message_from_child[1024];
    pid_t child[3];

    int fds[2];
    pipe(fds);
    for (int i =0; i < 3; i++) {
        sprintf(message_to_child, "hello child %d", i);
        child[i] = fork();
        if (child[i] == 0) {
            close(fds[0]);
            printf("parent said %s\n", message_to_child);
            sprintf(message_from_child, "hello parent from %d", i);
            if (write(fds[1], "hello", 6) != 6) {
                perror("write");
            }
            exit(0);
        }
        close(fds[1]);
        printf("%d started\n", child[i]);
    }
    for (int i = 0; i < 3; i++) {
        pid_t pid = wait(NULL);
        printf("%d finished\n", pid);
    }
    if (read(fds[0], message_from_child, 6) != 6) {
        perror("read");
    }
    printf("child said %s\n", message_from_child);
    exit(0);
}
