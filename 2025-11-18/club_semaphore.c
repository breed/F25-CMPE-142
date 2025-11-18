#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct person {
    char *name;
    int duration;
};

char *name[] = {
    "abe",
    "amy",
    "cal",
    "carrie",
    "terry",
    "berry",
    "sherry",
    "ben",
    "jen",
    "ken",
};

sem_t door;

void *enter_club(void *v)
{
    struct person *p = v;
    printf("= %s is waiting\n", p->name);
    sem_wait(&door);
    printf("+ %s entered club\n", p->name);
    sleep(p->duration);
    printf("- %s left club after %d seconds\n", p->name, p->duration);
    sem_post(&door);
    printf("! %s actually left\n", p->name);
}

int main()
{
    pthread_t ph[10];
    struct person people[10];

    sem_init(&door, 0, 0);
    for (int i = 0; i < 10; i++) {
        people[i].name = name[i];
        people[i].duration = 5 + (i%2);
    }

    for (int i = 0; i < 10; i++) {
        pthread_create(&ph[i], NULL, enter_club, &people[i]);
    }

    sleep(7);
    printf("we have a line! let's let 2 in\n");
    sem_post(&door);
    sem_post(&door);

    for (int i = 0; i < 10; i++) {
        pthread_join(ph[i], NULL);
    }
}
