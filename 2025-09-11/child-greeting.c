#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

static void showchildren(char *argv0) {
    char *progname = strrchr(argv0, '/');
    if (progname) {
        // we found the last slash, so skip it
        progname++;
    } else {
        progname = argv0;
    }
    char *cmd;
    asprintf(&cmd, "ps uxawww| grep %s", progname);
    printf("\nShowing the kids\n");
    system(cmd);
    printf("\n");
}

int main(int argc, char **argv) {
    char message_to_child[1024];
    char message_from_child[1024];
    pid_t child[3];

    int cfds[3][2];

    for (int i =0; i < 3; i++) {
        sprintf(message_to_child, "hello child %d", i);
        if (pipe(cfds[i]) == -1) {
            perror("pipe");
        }
        child[i] = fork();
        if (child[i] == 0) {
            // the child isn't going to read from the pipe, so close it
            close(cfds[i][0]);
            printf("parent said %s\n", message_to_child);
            sprintf(message_from_child, "hello parent from %d", i);
            if (write(cfds[i][1], message_from_child, strlen(message_from_child)+1) != strlen(message_from_child)+1) {
                perror("write");
            }
            exit(0);
        }

        // the parent isn't going to write to the pipe, so close it
        close(cfds[i][1]);
        printf("%d started\n", child[i]);
    }

    for (int i = 0; i < 3; i++) {
        if (read(cfds[i][0], message_from_child, sizeof message_from_child) <= 0) {
            perror("read");
        }
        printf("child said %s\n", message_from_child);
    }

    // since we haven't waited for the children, they are zombies
    // show the zombie children
    showchildren(argv[0]);

    for (int i = 0; i < 3; i++) {
        pid_t pid = wait(NULL);
        printf("%d finished\n", pid);
    }
    // zombies should be gone
    showchildren(argv[0]);
    exit(0);
}
