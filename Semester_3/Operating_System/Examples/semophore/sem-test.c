/*
 * semaphore/sem-test.c --
 *
 * This file implements test cases for our counting semaphores on top
 * of pthread mutexes and condition variables.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <pthread.h>
#include "sem.h"

static semaphore_t sem1, sem2;

/*
 * Wrapper functions so we do not have to have explicit error handling
 * code everywhere. If a semaphore operation fails, we can't do
 * anything meaningful anymore and we better quit.
 */

static void
down(semaphore_t *s)
{
    if (semaphore_down(s) < 0) exit(EXIT_FAILURE);
}

static void
up(semaphore_t *s)
{
    if (semaphore_up(s) < 0) exit(EXIT_FAILURE);
}

static void *
test1(void *ignored)
{
    (void) ignored;

    down(&sem1);
    /* critical section */
    up(&sem1);

    up(&sem2);
    up(&sem2);
    /* ??? */
    down(&sem2);
    down(&sem2);

    down(&sem1);
    /* critical section */
    up(&sem1);

    return NULL;
}

/*
 * Some trivial test code to be inserted here...
 */

int
main(void)
{
    pthread_t ptid1, ptid2;

    if (semaphore_init(&sem1, 1) != 0) {
	return EXIT_FAILURE;
    }

    if (semaphore_init(&sem2, 0) != 0) {
	return EXIT_FAILURE;
    }

    (void) pthread_create(&ptid1, NULL, test1, NULL);
    (void) pthread_create(&ptid2, NULL, test1, NULL);

    (void) pthread_join(ptid2, NULL);
    (void) pthread_join(ptid1, NULL);

    return 0;
}
