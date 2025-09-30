#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void signal_handler(int signum) {
    printf("got signal %d\n", signum);
}

int main(int argc, char **argv) {
    struct sigaction sa = { .sa_handler = signal_handler, .sa_flags = SA_RESTART };
    sigaction(SIGALRM, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGKILL, &sa, NULL);
    pid_t child = fork();
    if (child == 0) {
        execlp("./testing.sh", "super-test", "5309", NULL);
        exit(99);
    }
    alarm(2);
    int status;
    pid_t waited_pid = wait(&status);
    if (waited_pid == -1) {
        perror("wait");
    }
    if (WIFEXITED(status)) {
        printf("all done exit code %d\n", WEXITSTATUS(status));
    } else {
        printf("signaled with %d\n", WTERMSIG(status));
    }
}
