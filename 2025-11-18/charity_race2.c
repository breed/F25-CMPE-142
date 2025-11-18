#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>

pthread_mutex_t door;
pthread_cond_t bell;
volatile int club_count = 0;
int club_limit = 2;
sem_t gate;

// milestone counters
atomic_long mutex_milestones = 0;
atomic_long semaphore_milestones = 0;

void *mutex_racer(void *v)
{
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&door);
        atomic_fetch_add(&mutex_milestones, 1);
        pthread_mutex_unlock(&door);
    }
    printf("mutex racer finished %ld\n", atomic_load(&mutex_milestones));
}

void *semaphore_racer(void *v)
{
    for (int i = 0; i < 10000000; i++) {
        sem_wait(&gate);
        atomic_fetch_add(&semaphore_milestones, 1);
        sem_post(&gate);
    }
    printf("semaphore racer finished %ld\n", semaphore_milestones);
}

int main()
{
    pthread_t ph[20];

    pthread_mutex_init(&door, NULL);
    pthread_cond_init(&bell, NULL);
    sem_init(&gate, 0, 2);
    for (int i = 0; i < 20; i += 2) {
        pthread_create(&ph[i], NULL, mutex_racer, NULL);
        pthread_create(&ph[i+1], NULL, semaphore_racer, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(ph[i], NULL);
    }
}
