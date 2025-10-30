#include <stdio.h>
#include <pthread.h>
// for atomic_exchange
#include <stdatomic.h>

static int counter = 0;

pthread_mutex_t counter_lock;

pthread_mutexattr_t recursive_attr;

// mythread()
//
// Simply adds 1 to counter repeatedly, in a loop
// No, this is not how you would add 10,000,000 to
// a counter, but it shows the problem nicely.
//
void *mythread(void *arg) {
    printf("%s: begin\n", (char *) arg);
    int i;
    for (i = 0; i < 1e7; i++) {
        pthread_mutex_lock(&counter_lock);
        counter++;
        pthread_mutex_unlock(&counter_lock);
    }
    printf("%s: done\n", (char *) arg);
    return NULL;
}

// main()
//
// Just launches two threads (pthread_create)
// and then waits for them (pthread_join)
//
int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    pthread_mutexattr_init(&recursive_attr);
    pthread_mutexattr_settype(&recursive_attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&counter_lock, NULL);
    printf("main: begin (counter = %d)\n", counter);
#if 0
    mythread("A");
    mythread("B");
#else
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");

    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
#endif
    printf("main: done with both (counter = %d)\n", counter);
    return 0;
}
