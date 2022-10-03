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

pthread_mutex_t *mutex;
static const char *progname = "prisoner";
static uint32_t m_in_critical_region = 0;

#define CRITICAL_SECTION_ENTER()   \
    {                              \
        pthread_mutex_lock(mutex); \
        ++m_in_critical_region;    \
    }

#define CRITICAL_SECTION_EXIT()          \
    {                                    \
        if (--m_in_critical_region == 0) \
        {                                \
            pthread_mutex_unlock(mutex); \
        }                                \
    }

typedef struct
{
    int card;
    bool opened;
} drawer_t;

static double timeit(int n, void *(*proc)(void *));
void run_threads(int size, void *(*proc)(void *));

void initialize(int num_of_prisoners);
void *random_drawer(void *ptr);
void *random_global(void *ptr);
void *strategy_drawer(void *ptr);
void *strategy_global(void *ptr);

drawer_t *drawers;
const int num_of_prisoners = 100;
static uint64_t wins = 0;

int main(int argc, char **argv)
{
    srand(time(NULL));
    pthread_mutex_init(mutex, NULL);

    uint64_t num_of_games = 100;
    int seed;
    char *end;
    int c;

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

    for (uint64_t i = 0; i < num_of_games; i++)
    {
        initialize(num_of_prisoners);
        // wins += strategy...?
    }
    double time = 0.0;

    printf("method random_global    %9lu/%lu = %3.2lf%%  %3.3lf ms\n", wins, num_of_games, (100.0 * wins) / num_of_games, time);
    printf("method random_drawer    %9lu/%lu = %3.2lf%%  %3.3lf ms\n", wins, num_of_games, (100.0 * wins) / num_of_games, time);
    printf("method strategy_global  %9lu/%lu = %3.2lf%%  %3.3lf ms\n", wins, num_of_games, (100.0 * wins) / num_of_games, time);
    printf("method strategy_drawer  %9lu/%lu = %3.2lf%%  %3.3lf ms\n", wins, num_of_games, (100.0 * wins) / num_of_games, time);
    return EXIT_SUCCESS;
}

static double timeit(int n, void *(*proc)(void *))
{
    clock_t t1, t2;
    t1 = clock();
    run_threads(n, proc);
    t2 = clock();
    return ((double)t2 - (double)t1) / CLOCKS_PER_SEC * 1000;
}
void initialize(int num_of_prisoners)
{
    int j, card;
    bool unique;

    drawers = ((drawer_t *)malloc(num_of_prisoners * sizeof(drawer_t))) - 1;

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
void run_threads(int size, void *(*proc)(void *))
{
    pthread_t id[size];
    // creating the child threads
    for (int i = 1; i <= size; i++)
    {
        pthread_create(&id[i - 1], NULL, proc, NULL);
    }

    // joining the threads one by one
    for (int i = 1; i <= size; i++)
    {
        pthread_join(id[i - 1], NULL);
    }
}
void *random_drawer(void *ptr)
{
    int select;

    for (int i = 0; i < num_of_prisoners; i++)
    {
        bool foundCard = false;
        for (int j = 0; j < 50; j++)
        {
            do
            {
                select = rand() % num_of_prisoners + 1;
            } while (drawers[select].opened == true);

            CRITICAL_SECTION_ENTER();

            if (drawers[select].card == i)
            {
                foundCard = true;
                break;
            }
            drawers[select].opened = true;

            CRITICAL_SECTION_EXIT();
        }
        for (int i = 0; i < num_of_prisoners; i++)
        {
            drawers[i].opened = false;
        }
        if (foundCard == false)
        {
            // return true;
        }
    }

    // return false;
}
void *random_global(void *ptr)
{
    int select;

    for (int i = 0; i < num_of_prisoners; i++)
    {
        CRITICAL_SECTION_ENTER();

        bool foundCard = false;
        for (int j = 0; j < 50; j++)
        {
            do
            {
                select = rand() % num_of_prisoners + 1;
            } while (drawers[select].opened == true);

            if (drawers[select].card == i)
            {
                foundCard = true;
                break;
            }
            drawers[select].opened = true;
        }

        for (int i = 0; i < num_of_prisoners; i++)
        {
            drawers[i].opened = false;
        }

        CRITICAL_SECTION_EXIT();

        if (foundCard == false)
        {
            // return true;
        }
    }

    // return false;
}
void *strategy_drawer(void *ptr)
{
    int select;

    bool foundCard = false;
    for (int i = 0; i < num_of_prisoners; i++)
    {
        select = i;
        foundCard = false;
        for (int j = 0; j < 50; j++)
        {
            CRITICAL_SECTION_ENTER();
            drawers[select].opened = true;

            if (drawers[select].card == i)
            {
                foundCard = true;
                break;
            }
            if (select == drawers[select].card)
            {
                do
                {
                    select = rand() % num_of_prisoners + 1;
                } while (drawers[select].opened == true);
            }
            else
            {
                select = drawers[select].card;
            }

            CRITICAL_SECTION_EXIT();
        }

        for (i = 0; i < num_of_prisoners; i++)
        {
            drawers[i].opened = false;
        }
        if (foundCard == false)
        {
            // return true;
        }
    }

    // return false;
}
void *strategy_global(void *ptr)
{
    int select;

    bool foundCard = false;
    for (int i = 0; i < num_of_prisoners; i++)
    {
        CRITICAL_SECTION_ENTER();
        select = i;
        foundCard = false;
        for (int j = 0; j < 50; j++)
        {
            drawers[select].opened = true;

            if (drawers[select].card == i)
            {
                foundCard = true;
                break;
            }
            if (select == drawers[select].card)
            {
                do
                {
                    select = rand() % num_of_prisoners + 1;
                } while (drawers[select].opened == true);
            }
            else
            {
                select = drawers[select].card;
            }
        }

        for (i = 0; i < num_of_prisoners; i++)
        {
            drawers[i].opened = false;
        }
        CRITICAL_SECTION_EXIT();
        if (foundCard == false)
        {
            // return true;
        }
    }

    // return false;
}