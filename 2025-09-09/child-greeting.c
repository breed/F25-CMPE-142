#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main() {
    char message_to_child[1024];
    char message_from_child[1024];

    strcpy(message_to_child, "hello child");
    if (fork() == 0) {
        printf("parent said %s\n", message_to_child);
        strcpy(message_from_child, "hello parent");
        exit(0);
    }
    wait(NULL);
    printf("child said %s\n", message_from_child);
    exit(0);
}
