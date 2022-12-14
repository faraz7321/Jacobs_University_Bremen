#include <pthread.h>

int main(void)
{
    pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t  c = PTHREAD_COND_INITIALIZER;

    (void) pthread_mutex_lock(&m);
    (void) pthread_cond_wait(&c, &m);
    (void) pthread_cond_signal(&c);
    (void) pthread_mutex_unlock(&m);

    return 0;
}