/*
 * semaphore/sem.c --
 *
 * This file implements counting semaphores on top of pthread mutexes
 * and condition variables. For an explanation, see A.B. Downey: "The
 * Little Book of Semaphores".
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <pthread.h>
#include "sem.h"

/*
 * Create a new semaphore (kind of a constructor).
 */

int
semaphore_init(semaphore_t *sem, int value)
{
    sem->value = value;
    sem->wakeups = 0;
    if (pthread_mutex_init(&sem->mutex, NULL) != 0) {
	return -1;
    }
    if (pthread_cond_init(&sem->cond, NULL) != 0) {
	return -2;
    }
    return 0;
}

/*
 * Implementation of the down operation of our semaphore.
 */

int
semaphore_down(semaphore_t *sem)
{
    if (pthread_mutex_lock(&sem->mutex) != 0) {
	return -1;
    }
    sem->value--;

    if (sem->value < 0) {
	do {
	    if (pthread_cond_wait(&sem->cond, &sem->mutex) != 0) {
		return -2;
	    }
	} while (sem->wakeups < 1);
	sem->wakeups--;
    }

    if (pthread_mutex_unlock(&sem->mutex) != 0) {
	return -3;
    }

    return 0;
}

/*
 * Implementation of the up operation of our semaphore.
 */

int
semaphore_up(semaphore_t *sem)
{
    if (pthread_mutex_lock(&sem->mutex) != 0) {
	return -1;
    }
    sem->value++;

    if (sem->value <= 0) {
	sem->wakeups++;
	if (pthread_cond_signal(&sem->cond) != 0) {
	    return -2;
	}
    }

    if (pthread_mutex_unlock(&sem->mutex) != 0) {
	return -3;
    }

    return 0;
}
