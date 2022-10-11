/*
 * Faraz Ahmad
 * fa.ahmad@jacobs-university.de
 * CO-562 Operating Systems
 * account.c
 */

#include <pthread.h>
#include <stdio.h>
typedef struct account
{
    unsigned int number;
    unsigned int money;
    pthread_mutex_t lock;
} account_t;
typedef struct arg_data
{
    unsigned int money;
    account_t *to;
    account_t *from;
} arg_data_t;

static double timeit(int n, void *(*proc)(void *));
void run_threads(int num_of_prisoners, void *(*proc)(void *), arg_data_t args[]);
void *transfer(void *ptr);
void __init();
account_t from;
account_t to;

int main()
{
    unsigned int money = 100;
    __init();
    // printf("INITIALIZED\n");
    arg_data_t args = {.from = &from, .to = &to, .money = money};
    run_threads(1, transfer, &args);
    printf("from: %u\nmoney: %u\n", from.number, from.money);
    printf("to: %u\nmoney: %u\n", to.number, to.money);
}
void __init()
{
    from.number = 1;
    from.money = 10000;
    pthread_mutex_init(&from.lock, NULL);
    to.number = 2;
    to.money = 10000;
    pthread_mutex_init(&to.lock, NULL);
}
void run_threads(int num, void *(*proc)(void *), arg_data_t args[])
{

    pthread_t id[num];
    // creating the child threads
    // printf("Creating threads\n");
    for (int i = 0; i < num; i++)
    {
        pthread_create(&id[i], NULL, proc, &args[i]);
    }
    // printf("Joining threads\n");
    //  joining the threads one by one
    for (int i = 0; i < num; i++)
    {
        pthread_join(id[i], NULL);
    }
}
void *transfer(void *ptr)
{
    arg_data_t *args = (arg_data_t *)ptr;

    // results in deadlock
    pthread_mutex_lock(&args->from->lock);
    pthread_mutex_lock(&args->to->lock);
    args->from->money -= args->money;
    args->to->money += args->money;
    pthread_mutex_unlock(&args->to->lock);
    pthread_mutex_unlock(&args->from->lock);
}