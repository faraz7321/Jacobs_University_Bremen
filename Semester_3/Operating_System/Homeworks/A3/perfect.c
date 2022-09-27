
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

// defines
#define PRINTF(__fmt, ...)                                                           \
    do                                                                               \
    {                                                                                \
        fprintf(stderr, "perfect: t%d searching [%lu,%lu]\n", __fmt, ##__VA_ARGS__); \
    } while (0)

#define START 1
#define END 10000

typedef struct argData
{
    int thread_number;
} argData_t;

// function prototypes
static int is_perfect(uint64_t);
static void *start_routine(void *);
static int counter;

// Global static variables
static uint64_t s = START;
static uint64_t e = END;
int num_threads = 1;
static uint64_t interval;
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
    argData_t arg_arr[num_threads];
    interval = e - s + 1;

    start = clock();

    // creating the child threads
    for (thread_no = 1; thread_no <= num_threads; thread_no++)
    {
        arg_arr[thread_no - 1].thread_number = thread_no;
        pthread_create(&id[thread_no - 1], NULL, start_routine, &arg_arr[thread_no - 1]);
    }

    // joining the threads one by one
    for (int i = 1; i <= num_threads; i++)
    {
        pthread_join(id[i - 1], NULL);
        if (DEBUGMOD)
        {
            fprintf(stderr, "perfect: t%d finishing\n", i - 1);
        }
    }

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // printf("threads completed\n");
    printf("Time taken= %lf\n", time_taken);

    return 0;
}

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

void *start_routine(void *arg)
{
    argData_t *current_thread_data = (argData_t *)arg;

    uint64_t endpart = ((current_thread_data->thread_number) * ((interval) / num_threads));
    uint64_t startpart = endpart - (interval / num_threads) + 1;

    if (DEBUGMOD)
    {
        fprintf(stderr, "perfect: t%d searching [%lu,%lu]\n", current_thread_data->thread_number - 1, startpart, endpart);
    }
    for (uint64_t i = startpart; i < endpart; i++)
    {
        if (is_perfect(i))
        {
            printf("%lu\n", i);
        }
    }

    return NULL;
}