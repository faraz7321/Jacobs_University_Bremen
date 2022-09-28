/*
 * Faraz Ahmad
 * fa.ahmad@jacobs-university.de
 * CO-562 Operating Systems
 * perfect.c
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
#define DEBUG 1

#if DEBUG == 0
#define PRINTF(__fmt, ...)                     \
    do                                         \
    {                                          \
        fprintf(stderr, __fmt, ##__VA_ARGS__); \
    } while (0)

#elif DEBUG == 1
#define PRINTF(__fmt, ...)                                                           \
    do                                                                               \
    {                                                                                \
        fprintf(stderr, "perfect: t%d searching [%lu,%lu]\n", __fmt, ##__VA_ARGS__); \
    } while (0)

#endif

typedef struct argData
{
    int thread_number;
    uint64_t start, end;
} argData_t;

// function prototypes
static int is_perfect(uint64_t);
static void *start_routine(void *);
static int counter;

// Global static variables//
// default start and end
static uint64_t s = 1;
static uint64_t e = 10000;
static uint64_t interval;

// threads
int num_threads = 1;

// select debug mod
static int DEBUGMOD = 0;

int main(int argc, char *argv[])
{
    clock_t start, end;
    double time_taken;
    int thread_no = 1;

    //  checking arguments for options
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 's')
            {
                s = atoi(argv[i + 1]);
            }
            if (argv[i][1] == 'e')
            {
                e = atoi(argv[i + 1]);
            }
            if (argv[i][1] == 't')
            {
                num_threads = atoi(argv[i + 1]);
            }
            if (argv[i][1] == 'v')
            {
                DEBUGMOD = 1;
            }
        }
    }

    pthread_t id[num_threads];
    argData_t arg_arr[num_threads]; // struct to pass data
    interval = e - s + 1;

    start = clock();

    // creating the child threads
    for (thread_no = 1; thread_no <= num_threads; thread_no++)
    {
        arg_arr[thread_no - 1].thread_number = thread_no;
        arg_arr[thread_no - 1].end = ((thread_no) * ((interval) / num_threads));
        arg_arr[thread_no - 1].start = arg_arr[thread_no - 1].end - (interval / num_threads) + 1;
        pthread_create(&id[thread_no - 1], NULL, start_routine, &arg_arr[thread_no - 1]);
    }

    // joining the threads one by one
    for (int i = 1; i <= num_threads; i++)
    {
        pthread_join(id[i - 1], NULL);
        if (DEBUGMOD)
        {
            fprintf(stderr, "perfect: t%d finishing\n", i - 1);
            // PRINTF(stderr, "perfect: t%d finishing\n", i - 1);
        }
    }

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // PRINTF("threads completed\n");
    printf("Time taken= %lf\n", time_taken);

    return 0;
}

/**
 * @brief checks number if perfect
 *
 * @param num
 * @return int
 */
static int is_perfect(uint64_t num)
{
    uint64_t i, sum;
    if (num < 2)
    {
        return 0;
    }
    for (i = 2, sum = 1; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            sum += (i * i == num) ? i : i + num / i;
        }
    }
    return (sum == num);
}

/**
 * @brief routine process
 *
 * @param arg
 * @return void*
 */
void *start_routine(void *arg)
{
    argData_t *current_thread_data = (argData_t *)arg;

    if (DEBUGMOD)
    {
        PRINTF(current_thread_data->thread_number - 1, current_thread_data->start, current_thread_data->end);
    }
    for (uint64_t i = current_thread_data->start; i < current_thread_data->end; i++)
    {
        if (is_perfect(i))
        {
            printf("%lu\n", i);
            // PRINTF("%lu\n", i);
        }
    }

    return NULL;
}