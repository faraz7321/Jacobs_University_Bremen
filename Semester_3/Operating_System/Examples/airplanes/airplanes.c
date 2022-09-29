/*
 *============================================================================
 * Name        : airplanes.c
 * Author      : Alen Stojanov
 * Version     : 1.0
 * Copyright   : GNU GPL License
 * Description : Example in Thread Synchronization
 *============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/*
 * Data structure to represent the different planes used
 * in the threads.
 */
typedef struct {
    int id;             /* The ID of the airplane */
    pthread_t tid;      /* The thread ID of the airplane */
} planes_t;


sem_t runway_sem;       /* The semaphore used for the runways */
sem_t queue_sem;        /* The semaphore used for the gate queue */
sem_t queue_mutex;      /* Auxiliary semaphore, to ensure that 3 planes
                           proceed to the gates */


/*
 * The plane must call plane_land to get permission for landing
 */
static void
plane_land(int id)
{
    printf("[PL]: Airplane %d requests permission to land\n", id);
    sem_wait(&runway_sem);
    printf("[LG]: ===> Airplane %d has landed\n", id);
}

/*
 * The plane must call plane_queue to proceed to the gates. Meanwhile
 * the plane waits on the runway.
 */
static void
plane_queue(int id)
{
    int sval;

    printf("[PG]: Airplane %d requests permission to proceed to the gates\n", id);
    
    sem_wait(&queue_sem);
    
    sem_getvalue(&queue_sem, &sval);
    if (sval != 0) {
        sem_wait(&queue_mutex);
    } else {
        sem_post(&queue_mutex);
        sem_post(&queue_mutex);
    }
    
    sem_post(&runway_sem);
    
    printf("[GG]: ===> Airplane %d did proceed to gate: %d\n", id, 3 - sval);
    
    sem_post(&queue_sem);
}


/*
 * The simple thread function. Every airplane will try to land.
 * After the plane has landed, it proceeds to the gates in queue.
 */
static void*
plane_function(void* args)
{
    planes_t* plane = (planes_t*)args;
    
    plane_land(plane->id);
    plane_queue(plane->id);
    
    return NULL;
}

/*
 * Display usage information on the stderr stream.
 */
static void
usage(char** argv)
{
    fprintf(stderr, "Usage: %s num_planes num_runways\n", argv[0]);
}

/*
 * The main function and entry point.
 */
int
main(int argc, char* argv[])
{
    int n = 0, m = 0, i, status;
    planes_t* planes;
    
    if (argc != 3) {
        usage(argv);
        exit(EXIT_FAILURE);
    }
    
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    if (n <= 0 || m < 3) {
        usage(argv);
        exit(EXIT_FAILURE);
    }

    if (sem_init(&runway_sem, 0, m)
        || sem_init(&queue_sem, 0, 3) 
        || sem_init(&queue_mutex, 0, 0)) {
        fprintf(stderr, "%s: initialization of semaphores failed\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    planes = (planes_t *)calloc(n, sizeof(planes_t));
    if (!planes) {
        fprintf(stderr, "%s: out of memory\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i < n; i++) {
        planes[i].id = i + 1;
        status = pthread_create(&planes[i].tid, NULL,
                                plane_function, (void*)&planes[i]);
        if (status != 0) {
            fprintf(stderr, "%s: pthread_create() failed: %d\n",
                    argv[0], status);
        }
    }
    
    for (i = 0; i < n; i++) {
        pthread_join( planes[i].tid, NULL);
    }
    
    (void) free(planes);
    
    if (sem_destroy(&runway_sem)
        || sem_destroy(&queue_sem)
        || sem_destroy(&queue_mutex)) {
        fprintf(stderr, "%s: destruction of semaphores failed\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS;
}
