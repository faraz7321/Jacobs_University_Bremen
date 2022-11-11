/*
 * pthread/pthread-fib.c --
 *
 *	A simple program to compute numbers: ./pthread-fib $(seq 0 12)
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void* foo(void *arg)
{
    volatile uintptr_t num = (uintptr_t) arg;
    volatile uintptr_t n1 = num - 1, n2 = num - 2;
    pthread_t tid1, tid2;

    if (num > 1) {
	(void) pthread_create(&tid1, NULL, foo, (void *) n1);
	(void) pthread_create(&tid2, NULL, foo, (void *) n2);

	(void) pthread_join(tid1, (void **) &n1);
	(void) pthread_join(tid2, (void **) &n2);
	num = n1 + n2;
    }
    return (void *) num;
}

int main(int argc, char *argv[])
{
    int rc = EXIT_SUCCESS;
    
    for (int i = 1; i < argc; i++) {
	char *endptr;
	long l = strtol(argv[i], &endptr, 10);
	if (! endptr || *endptr != '\0' || l < 0) {
	    fprintf(stderr,
		    "argument '%s' must be a positive integer\n", argv[i]);
	    rc = EXIT_FAILURE;
	    continue;
	}
	volatile uintptr_t num = atoi(argv[i]);
	void *ptr = foo((void *) num);
	printf("%ld\t%ld\n", l, (uintptr_t) ptr);
    }

    return rc;
}
