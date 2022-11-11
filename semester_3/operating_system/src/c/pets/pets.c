/*
 * pets/pets.c --
 *
 *	Solution for the cats and mice synchronization problem.
 *	Written by Matus Harvan, subsequently modified by Juergen
 *	Schoenwaelder.
 */

#define _REENTRANT
#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>

#define N_DISHES        2       /* number of dishes */
#define N_CATS          6       /* number of cats */
#define N_MICE          2       /* number of mice */

#define CAT_WAIT        15      /* max time in seconds a cat sleeps */
#define CAT_EAT         1       /* how long in seconds a cat is eating */
#define CAT_N_EAT       4       /* how many times a cat wants to eat */
#define MOUSE_WAIT      1       /* max time in seconds a mouse sleeps */
#define MOUSE_EAT       1       /* how long in seconds a mouse is eating */
#define MOUSE_N_EAT     4       /* how many times a mouse wants to eat */

typedef struct dish {
    int free_dishes;            /* how many dishes are free */
    int cats_eating;            /* how many cats are eating at the moment */
    int mice_eating;            /* how many mice are eating at the moment */
    int cats_waiting;           /* how many cats are waiting for dish */
    enum {
        none_eating,
        cat_eating,
        mouse_eating
    } status[N_DISHES];         /* status of each dish */
    pthread_mutex_t mutex;      /* mutex for accessing dish */
    pthread_cond_t free_cv;     /* used to wait for a free dish */
    pthread_cond_t cat_cv;      /* used to wait for coming cats */
} dish_t;

#define PET_CAT		"cat"
#define PET_MOUSE	"mouse"

typedef struct pet {
    pthread_t thread;
    const char *kind;
    unsigned id;
    dish_t *dish;
} pet_t;

static const char *progname = "pets";

/* 
 * Just for debugging, dump the content of the shared data structure.
 */

static void
dump_dish(pet_t *pet, const char *what, dish_t *dish, int my_dish)
{
    int i;
    struct tm t;
    time_t tt;
    
    tt = time(NULL);
    assert(tt != (time_t) -1);
    localtime_r(&tt, &t);

    printf("%02d:%02d:%02d [", t.tm_hour, t.tm_min, t.tm_sec);
    for (i = 0; i < N_DISHES; i++) {
        if (i) printf(":");
        switch (dish->status[i]) {
        case none_eating:
            printf("-");
            break;
        case cat_eating:
            printf("c");
            break;
        case mouse_eating:
            printf("m");
            break;
        }
    }
    printf("] %s %d %s eating from dish %d\n",
	   pet->kind, pet->id, what, my_dish);
}

/*
 * Cats wait for a dish to become free and when coming to the dish,
 * they wait for the mice to run away from the dish (they are nice
 * cats and want to eat dish rather than mice). Eating is simulated
 * by a simple sleep().
 */

static void* 
cat(void *arg)
{
    pet_t *pet = (pet_t *) arg;
    dish_t *dish = pet->dish;
    int n = CAT_N_EAT;
    int my_dish = -1;
    int i;

    for (n = CAT_N_EAT; n > 0; n--) {

        pthread_mutex_lock(&dish->mutex);
        /* wait for a dish to become free */
        pthread_cond_broadcast(&dish->cat_cv);
        dish->cats_waiting++;
        while (dish->free_dishes <= 0 || dish->mice_eating > 0) {
            pthread_cond_wait(&dish->free_cv, &dish->mutex);
        }
        dish->cats_waiting--;

        /* starting to eat - first check everything is fine... */
        assert(dish->free_dishes > 0);
        dish->free_dishes--;
        assert(dish->cats_eating < N_CATS);
        dish->cats_eating++;
        
        /* ...then find the first available free dish */
        for (i = 0; i < N_DISHES && dish->status[i] != none_eating; i++) ;
        my_dish = i;
        assert(dish->status[my_dish] == none_eating);
        dish->status[my_dish] = cat_eating;
        dump_dish(pet, "started", dish, my_dish);
        pthread_mutex_unlock(&dish->mutex);

        /* cats simply eat - mice avoid meeting cats for obvious reasons */
        sleep(CAT_EAT);
        
        /* finished eating - check everything is fine and update state */
        pthread_mutex_lock(&dish->mutex);
        assert(dish->free_dishes < N_DISHES);
        dish->free_dishes++;
        assert(dish->cats_eating > 0);
        dish->cats_eating--;
        dish->status[my_dish] = none_eating;

        /* finally  tell others we're done eating */
        pthread_cond_broadcast(&dish->free_cv);
        dump_dish(pet, "finished", dish, my_dish);
        pthread_mutex_unlock(&dish->mutex);

        /* sleep some time to give others a chance to grab some food */
        sleep(rand() % CAT_WAIT);
    }

    return NULL;
}

/*
 * Mice wait for a dish to become free and cats go away. While eating,
 * they have to check that no cat is coming. Hence, a simple sleep()
 * cannot be used.
 */

static void* 
mouse(void *arg)
{
    pet_t *pet = (pet_t *) arg;
    dish_t *dish = pet->dish;
    int n = MOUSE_N_EAT;
    struct timespec ts;
    struct timeval tp;
    int my_dish;
    int i;

    for (n = MOUSE_N_EAT; n > 0; n--) {

        pthread_mutex_lock(&dish->mutex);
        /* wait for a dish to become free and cats go away */
        while (dish->free_dishes <= 0 || dish->cats_eating > 0
               || dish->cats_waiting > 0) {
            pthread_cond_wait(&dish->free_cv, &dish->mutex);
        }

        /* starting to eat - first check everything is fine... */
        assert(dish->free_dishes > 0);
        dish->free_dishes--;
        assert(dish->cats_eating == 0);
        assert(dish->mice_eating < N_MICE);
        dish->mice_eating++;

        /* ...then find the first available free dish */
        for (i = 0; i < N_DISHES && dish->status[i] != none_eating; i++) ;
        my_dish = i;
        assert(dish->status[my_dish] == none_eating);
        dish->status[my_dish] = mouse_eating;
        dump_dish(pet, "started", dish, my_dish);
        pthread_mutex_unlock(&dish->mutex);
        
        /* eat - mice need to watch for cats becoming hungry */
        gettimeofday(&tp,NULL);
        ts.tv_sec  = tp.tv_sec;
        ts.tv_nsec = tp.tv_usec * 1000;
        ts.tv_sec += MOUSE_EAT;
        pthread_mutex_lock(&dish->mutex);
        pthread_cond_timedwait(&dish->cat_cv, &dish->mutex, &ts);
        pthread_mutex_unlock(&dish->mutex);
        
        /* finished eating - check everything is fine and update state */
        pthread_mutex_lock(&dish->mutex);
        assert(dish->free_dishes < N_DISHES);
        dish->free_dishes++;
        assert(dish->cats_eating == 0);
        assert(dish->mice_eating > 0);
        dish->mice_eating--;
        dish->status[my_dish]=none_eating;

        /* finally tell others we're done eating */
        pthread_cond_broadcast(&dish->free_cv);
        dump_dish(pet, "finished", dish, my_dish);
        pthread_mutex_unlock(&dish->mutex);
        
        /* sleep some time to give others a chance to grab some food */
        sleep(rand() % MOUSE_WAIT);
    }

    return NULL;
}

/*
 * Initialize the shared data object, kick off cat and mice threads
 * and wait until they are done.
 */

int
main(void)
{
    int i, err;
    dish_t _dish, *dish;
    pet_t cats[N_CATS];
    pet_t mice[N_MICE];

    srand(time(NULL));  /* initialize random number generator */

    dish = &_dish;
    memset(dish, 0, sizeof(dish_t));
    dish->free_dishes = N_DISHES;
    pthread_mutex_init(&dish->mutex, NULL);
    pthread_cond_init(&dish->free_cv, NULL);
    pthread_cond_init(&dish->cat_cv, NULL);
    
    /* create cats */
    for (i = 0; i < N_CATS; i++) {
        err = pthread_create(&cats[i].thread, NULL, cat, &cats[i]);
        if (err != 0) {
            fprintf(stderr, "%s: %s(): unable to create cat thread %d: %s\n",
                    progname, __func__, i, strerror(err));
        }
	cats[i].kind = PET_CAT;
	cats[i].id = i;
	cats[i].dish = dish;
    }

    /* create mice */
    for (i = 0; i < N_MICE; i++) {
        err = pthread_create(&mice[i].thread, NULL, mouse, &mice[i]);
        if (err != 0) {
            fprintf(stderr, "%s: %s(): unable to create mouse thread %d: %s\n",
                    progname, __func__, i, strerror(err));
        }
	mice[i].kind = PET_MOUSE;
        mice[i].id = i;
	mice[i].dish = dish;
    }

    /* join all pets */
    for (i = 0; i < N_CATS; i++) {
        (void) pthread_join(cats[i].thread, NULL);
    }
    for (i = 0; i < N_MICE; i++) {
        (void) pthread_join(mice[i].thread, NULL);
    }
    
    pthread_mutex_destroy(&dish->mutex);
    pthread_cond_destroy(&dish->free_cv);
    pthread_cond_destroy(&dish->cat_cv);
    
    return EXIT_SUCCESS;
}
