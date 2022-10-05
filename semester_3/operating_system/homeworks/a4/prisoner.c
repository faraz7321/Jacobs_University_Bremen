/*
 * Faraz Ahmad
 * fa.ahmad@jacobs-university.de
 * CO-562 Operating Systems
 * prisoner.c
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdarg.h>
#include <time.h>

// number of total prisoners
#define PRISONERS 100

typedef struct
{
    int card;
    bool opened;
} drawer_t;

/** GLOBAL VARIABLES **/
static const char *progname = "prisoner";

// mutexes
pthread_mutex_t mutex;
pthread_mutex_t mutexes[100];

// program specific
drawer_t *drawers;
static uint64_t wins = 0;
bool victory = true;

/** FUNCTION PROTOTYPES **/
// thread functions
static double timeit(int n, void *(*proc)(void *));
void run_threads(int num_of_prisoners, void *(*proc)(void *));

// utility functions
void initialize(int num_of_prisoners);
void resetDrawers(int num_of_prisoners);
void run_games(char *game, void *(*proc)(void *), uint64_t n);

// routines
void *random_drawer(void *ptr);
void *random_global(void *ptr);
void *strategy_drawer(void *ptr);
void *strategy_global(void *ptr);

int main(int argc, char **argv)
{
    uint64_t num_of_games = 100;
    int seed;
    int c;

    srand(time(NULL));

    // initialize mutexes
    for (int i = 0; i < PRISONERS; ++i)
    {
        pthread_mutex_init(&mutexes[i], NULL);
    }
    pthread_mutex_init(&mutex, NULL);

    // get command line arguments options
    while ((c = getopt(argc, argv, "n:s:h")) != -1)
    {
        switch (c)
        {
        case 'n':
        {
            if ((num_of_games = atoi(optarg)) <= 0)
            {
                fprintf(stderr, "number of games must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        }
        case 's':
        {
            if ((seed = atoi(optarg)) <= 0)
            {
                fprintf(stderr, "number of seed must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        }
        case 'h':
        {
            printf("Usage: %s [-s seed] [-n games] [-h help]", progname);
            exit(EXIT_SUCCESS);
        }
        default:
            break;
        }
    }

    // run all four strategies
    run_games("random_drawer  ", random_drawer, num_of_games);
    run_games("random_global  ", random_global, num_of_games);
    // run_games("strategy_drawer", strategy_drawer, num_of_games);
    run_games("strategy_global", strategy_global, num_of_games);

    return EXIT_SUCCESS;
}

/**
 * @brief runs a single strategy n times
 *
 * @param game
 * @param proc
 * @param n
 */
void run_games(char *game, void *(*proc)(void *), uint64_t num_of_games)
{
    wins = 0;
    double time = 0.0;
    for (int i = 0; i < num_of_games; ++i)
    {
        initialize(PRISONERS);
        time += timeit(PRISONERS, proc);
    }
    printf("method %s     %9lu/%lu = %2.2lf%%  %3.3lf ms\n", game, wins, num_of_games, (100.0 * wins) / num_of_games, time);
}

/**
 * @brief initialize drawers
 *
 * @param num_of_prisoners
 */
void initialize(int num_of_prisoners)
{
    free(drawers);
    int j, card;
    bool unique;

    drawers = ((drawer_t *)malloc(num_of_prisoners * sizeof(drawer_t)));

    card = rand() % num_of_prisoners + 1;
    drawers[0] = (drawer_t){.card = card, .opened = false};

    for (int i = 1; i < num_of_prisoners; i++)
    {
        unique = false;
        while (unique == false)
        {
            for (j = 0; j < i; j++)
            {
                if (drawers[j].card == card)
                {
                    card = rand() % num_of_prisoners + 1;
                    break;
                }
            }
            if (j == i)
            {
                unique = true;
            }
        }
        drawers[i] = (drawer_t){.card = card, .opened = false};
    }
}

/**
 * @brief calculate time for a single game
 *
 * @param n
 * @param proc
 * @return double
 */
static double timeit(int n, void *(*proc)(void *))
{
    clock_t t1, t2;
    t1 = clock();
    run_threads(n, proc);
    t2 = clock();
    return ((double)t2 - (double)t1) / CLOCKS_PER_SEC * 1000;
}

/**
 * @brief creates n threads
 *
 * @param n
 * @param proc
 */
void run_threads(int num_of_prisoners, void *(*proc)(void *))
{
    pthread_t id[num_of_prisoners];
    victory = true;
    // creating the child threads
    for (int i = 0; i < num_of_prisoners; i++)
    {
        pthread_create(&id[i], NULL, proc, &i);
    }

    // joining the threads one by one
    for (int i = 0; i < num_of_prisoners; i++)
    {
        pthread_join(id[i], NULL);
    }

    if (victory)
    {
        wins += 1;
    }
}

void *random_drawer(void *ptr)
{
    int select;
    int *i = (int *)ptr;
    bool foundCard = false;

    bool is_drawer_opened[100];
    for (int j = 0; j < 100; j++)
    {
        is_drawer_opened[j] = false;
    }
    // printf("innnn %d\n", *i);
    for (int j = 0; j < 50; j++)
    {
        do
        {
            select = rand() % PRISONERS + 1;
        } while (is_drawer_opened[select]);
        // printf("in %d\n", j);
        pthread_mutex_lock(&mutexes[select]);

        if (drawers[select].card == *i)
        {
            foundCard = true;
            // printf("found\n");
            pthread_mutex_unlock(&mutexes[select]);
            break;
        }
        is_drawer_opened[select] = true;
        pthread_mutex_unlock(&mutexes[select]);
    }
    if (!foundCard)
    {
        victory = false;
    }
}

void *random_global(void *ptr)
{
    int *i = (int *)ptr;
    int select;

    pthread_mutex_lock(&mutex);

    bool foundCard = false;
    for (int j = 0; j < 50; j++)
    {
        do
        {
            select = rand() % PRISONERS + 1;
        } while (drawers[select].opened == true);

        if (drawers[select].card == *i)
        {
            foundCard = true;
            break;
        }
        drawers[select].opened = true;
    }

    resetDrawers(PRISONERS);

    if (!foundCard)
    {
        victory = false;
    }
    pthread_mutex_unlock(&mutex);
}

void *strategy_drawer(void *ptr)
{
    int select;
    int *i = (int *)ptr;
    bool foundCard = false;
    bool is_drawer_opened[100];
    for (int j = 0; j < 100; j++)
    {
        is_drawer_opened[j] = false;
    }
    select = *i;
    foundCard = false;
    for (int j = 0; j < 50; j++)
    {
        pthread_mutex_lock(&mutexes[select]);
        is_drawer_opened[select] = true;

        if (drawers[select].card == *i)
        {
            foundCard = true;
            pthread_mutex_unlock(&mutexes[select]);
            break;
        }
        if (select == drawers[select].card)
        {
            do
            {
                select = rand() % PRISONERS + 1;
            } while (is_drawer_opened[select]);
        }
        else
        {
            select = drawers[select].card;
        }

        pthread_mutex_unlock(&mutexes[select]);
    }

    if (!foundCard)
    {
        victory = false;
    }
}

void *strategy_global(void *ptr)
{
    int *i = (int *)ptr;
    int select;

    bool foundCard = false;
    pthread_mutex_lock(&mutex);
    select = *i;
    foundCard = false;
    for (int j = 0; j < 50; j++)
    {
        drawers[select].opened = true;

        if (drawers[select].card == *i)
        {
            foundCard = true;
            break;
        }
        if (select == drawers[select].card)
        {
            do
            {
                select = rand() % PRISONERS + 1;
            } while (drawers[select].opened == true);
        }
        else
        {
            select = drawers[select].card;
        }
    }

    resetDrawers(PRISONERS);
    if (!foundCard)
    {
        victory = false;
    }
    pthread_mutex_unlock(&mutex);
}

/**
 * @brief closes all drawers
 *
 * @param n
 */
void resetDrawers(int n)
{
    for (int j = 0; j < n; j++)
    {
        drawers[j].opened = false;
    }
}