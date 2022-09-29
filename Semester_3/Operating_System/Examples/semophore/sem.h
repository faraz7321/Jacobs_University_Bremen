/*
 * semaphore/sem.h --
 *
 * This file implements counting semaphores on top of pthread mutexes
 * and condition variables. For an explanation, see A.B. Downey: "The
 * Little Book of Semaphores".
 */

#ifndef _SEM_H_
#define _SEM_H_

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <pthread.h>

/*
 * A structure to describe a semaphore. The semaphore implementation
 * ensures that when a thread executes 'up' and there are waiting
 * threads, then one of the waiting threads will be woken. In
 * particular, it will not be possible for a thread to do an 'up'
 * followed by a 'down', bypassing any waiting threads. This ensures
 * that this kind of starvation can be avoided.
 */

typedef struct {
    int		    value;		/* value of the semaphore */
    int		    wakeups;		/* number of threads that have
					   been woken but have not yet
					   resumed execution */
    pthread_mutex_t mutex;		/* mutex to protect the semaphore */
    pthread_cond_t  cond;		/* condition variable to implement
					   the waiting behavior */
} semaphore_t;

extern int semaphore_init(semaphore_t *sem, int value);
extern int semaphore_down(semaphore_t *sem);
extern int semaphore_up(semaphore_t *sem);

#endif
