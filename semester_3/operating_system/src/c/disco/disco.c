/*
 * disco/disco.c --
 *
 *	Solution of the disco dancing problem (see problem sheet #2
 *      Spring 2012 for a description).
 *
 * Corneliu-Claudiu Prodescu <c.prodescu@jacobs-university.de>
 * Bogdan-Alexandru Matican <b.matican@jacobs-university.de>
 */

#define _REENTRANT
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define DANCE_TIME(x)   (((x) + 1) / 2)

const char* progname = "disco";

typedef struct _group {
    int id;
    int size;
    int people_arrived;
    int people_entered;
    pthread_mutex_t lock;
    sem_t barrier1;
    sem_t barrier2;
} group_t;

typedef struct _person {
    int id;
    group_t* group;
} person_t;

typedef struct _dancefloor {
    int group_size;
    pthread_cond_t dance_cond;
    pthread_cond_t wait_cond;
    pthread_mutex_t lock;
} dancefloor_t;

pthread_t   *threads;
person_t    *people;
group_t     *groups;
dancefloor_t dancefloor = {
    .group_size = 0,
    .dance_cond = PTHREAD_COND_INITIALIZER,
    .wait_cond = PTHREAD_COND_INITIALIZER,
    .lock = PTHREAD_MUTEX_INITIALIZER
};

/* Required methods */

void arrive(person_t *p);
void enter(person_t* p);
void start_dance(group_t *g);
void end_dance_interrupt(group_t *g);
void end_dance_success(group_t *g);
void leave(person_t *p);

/* Helpers */

void *person_thread(void* person);
void group_dance(group_t* g);
void print_usage_quit();

int main(int argc, char *argv[]) {
    int i, j, k;
    int total_threads = 0;

    if (argc < 2) {
        print_usage_quit();
    } 
    for (i = 1; i < argc; ++i) {
        char* endptr;
        int num = strtol(argv[i], &endptr, 10);
        if (num > 0 && *endptr == '\0') {
            total_threads += num;
        } else {
            fprintf(stderr, "%s: Argument \"%s\" invalid\n",
                    progname, argv[i]);
            print_usage_quit(argv[0]);
        }
    }
    groups = malloc(sizeof(group_t) * (argc - 1));
    people = malloc(sizeof(person_t) * total_threads);
    threads = malloc(sizeof(pthread_t) * total_threads);
    if (! groups || ! people || ! threads) {
        fprintf(stderr, "%s: Malloc failure\n", progname);
        exit(EXIT_FAILURE);
    }

    for (i = 1, k = 0; i < argc; ++i) {
        int num = strtol(argv[i], NULL, 10);
        // Group init
        groups[i-1].id = i;
        groups[i-1].size = num;
        groups[i-1].people_arrived = 0;
        groups[i-1].people_entered = 0;
        if (pthread_mutex_init(&groups[i-1].lock, NULL) != 0) {
            perror("pthread_mutex_init");
            exit(EXIT_FAILURE);
        }
        if (sem_init(&groups[i-1].barrier1, 0, 0) != 0) {
            perror("sem_init");
            exit(EXIT_FAILURE);
        }
        if (sem_init(&groups[i-1].barrier2, 0, 0) != 0) {
            perror("sem_init");
            exit(EXIT_FAILURE);
        }

        for (j = 0; j < num; ++j) {
            // Person init
            people[k].id = k + 1;
            people[k].group = &groups[i-1];
            if (pthread_create(&threads[k], NULL,
                               person_thread, &people[k]) != 0) {
                perror("pthread_create");
                exit(EXIT_FAILURE);
            }
            k++;
        }
    }
    for (i = 0; i < total_threads; ++i) {
        pthread_join(threads[i], NULL);
    }
    free(threads);
    free(people); // :D
    free(groups);

    return EXIT_SUCCESS;
}

void print_usage_quit() {
    fprintf(stderr, "Usage: %s grp_size ..\n", progname);
    exit(EXIT_FAILURE);
}

void *person_thread(void* arg) {
    person_t *p = (person_t*)arg;
    group_t *g = p->group;

    // ARRIVE
    pthread_mutex_lock(&g->lock);
    g->people_arrived++;
    arrive(p);

    // last arrived outside
    if (g->people_arrived == g->size) {
        int i;
        for (i = 0; i < g->size; ++i) sem_post(&g->barrier1);
        g->people_arrived = 0;
    }
    pthread_mutex_unlock(&g->lock);
    // Wait for others before entering
    sem_wait(&g->barrier1);

    // ENTER
    pthread_mutex_lock(&g->lock);
    g->people_entered++;
    enter(p);

    // last arrived inside
    if (g->people_entered == g->size) {
        int i;
        // Just the leader will coordinate the dance
        group_dance(g);
        for (i = 0; i < g->size; ++i) sem_post(&g->barrier2);
    }
    pthread_mutex_unlock(&g->lock);

    // Wait while leader coordinates the dance
    sem_wait(&g->barrier2);

    // LEAVE
    leave(p);

    return NULL;
}


void group_dance(group_t *g) {
    struct timespec ts;
    int rc;

    pthread_mutex_lock(&dancefloor.lock);

    while (1)
    {
        while (dancefloor.group_size >= g->size) {
            pthread_cond_wait(&dancefloor.wait_cond, &dancefloor.lock);
        }
        // Interrupting the dance, if any
        pthread_cond_broadcast(&dancefloor.dance_cond);
        dancefloor.group_size = g->size;

        // STARTING
        start_dance(g);

        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += DANCE_TIME(g->size);
        rc = pthread_cond_timedwait(&dancefloor.dance_cond,
				    &dancefloor.lock, &ts);
        if (rc == ETIMEDOUT) break;

        // INTERRUPTED
        end_dance_interrupt(g);
    }

    // Freeing the dancefloor
    dancefloor.group_size = 0;
    pthread_cond_broadcast(&dancefloor.wait_cond);
    // SUCCESS
    end_dance_success(g);

    pthread_mutex_unlock(&dancefloor.lock);
}

void arrive(person_t *p) {
    printf("Person %d of group %d has arrived (%d remaining)\n",
            p->id, p->group->id, p->group->size - p->group->people_arrived);
}

void enter(person_t* p) {
    printf("Person %d of group %d entering (%d remaining)\n",
            p->id, p->group->id, p->group->size - p->group->people_entered);
}

void start_dance(group_t *g) {
    printf("Group %d starts dancing\n", g->id);
}

void end_dance_interrupt(group_t *g) {
    printf("Group %d has lost dominance\n", g->id);
}

void end_dance_success(group_t *g) {
    printf("Group %d has finished dancing\n", g->id);
}

void leave(person_t *p) {
    printf("Person %d of group %d is leaving\n", p->id, p->group->id);
}
