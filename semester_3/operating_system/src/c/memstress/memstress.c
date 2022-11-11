/*
 * memstress/memstress.c --
 *
 * $ /usr/bin/time -v memstress
 *
 * Make sure you use GNU time and not the shell builtin time command.
 * Check whether major page faults actually occurred. Going column by
 * column order is generally slower even if the reason is not the
 * memory management system. Think about why this is the case...
 */

#define _POSIX_C_SOURCE 2
#define _DEFAULT_SOURCE
#define _DARWIN_C_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

static size_t size = 10000;
static long *m;                 /* 2-dimensional array m[size][size] */

static void *
libc_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (! ptr) {
        fprintf(stderr, "memory allocation failure (size %zd)\n", size);
	exit(EXIT_FAILURE);
    }
    return ptr;
}

static void
libc_free(void *ptr, size_t size)
{
    (void) size;
    (void) free(ptr);
}

static size_t
mmap_roundup(size_t size)
{
    long pagesize;

    pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1) {
	perror("sysconf");
	exit(EXIT_FAILURE);
    }

    return ((size + pagesize-1) & ~(pagesize-1));
}

static void *
mmap_malloc(size_t size)
{
    size_t length = mmap_roundup(size);
  
    m = mmap(NULL, length, PROT_READ | PROT_WRITE,
	     MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (m == MAP_FAILED) {
        fprintf(stderr, "memory allocation failure (size %zd): %s",
		size, strerror(errno));
	exit(EXIT_FAILURE);
    }
    return m;
}

static void
mmap_free(void *ptr, size_t size)
{
    size_t length = mmap_roundup(size);
  
    if (munmap(ptr, length) == -1) {
	perror("munmap");
	exit(EXIT_FAILURE);
    }
}

static void
init_rbr(long *m, size_t size)
{
    unsigned i, j;
    long l = 0;
    
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            m[i * size + j] = l++;
        }
    }
}

static void
init_cbc(long *m, size_t size)
{
    unsigned i, j;
    long l = 0;
    
    for (j = 0; j < size; j++) {
        for (i = 0; i < size; i++) {
            m[i * size + j] = l++;
        }
    }
}

int
main(int argc, char *argv[])
{
    int opt;
    int num;
    size_t length;
    void (*init)(long *m, size_t size) = init_rbr;
    void * (*malloc)(size_t size) = libc_malloc;
    void (*free)(void *ptr, size_t size) = libc_free;
    
    while ((opt = getopt(argc, argv, "crms:")) != -1) {
        switch (opt) {
	case 'c':
  	    init = init_cbc;
	    break;
        case 'r':
            init = init_rbr;
            break;
	case 'm':
 	    malloc = mmap_malloc;
	    free = mmap_free;
	    break;
        case 's':
            num = atoi(optarg);
            if (num <= 0) {
                fprintf(stderr, "%s: size must be a positive number\n",
                        argv[0]);
                exit(EXIT_FAILURE);
            }
            size = num;
            break;
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-c] [-r] [-m] [-s size]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    length = size * size * sizeof(long);
    printf("array size %zd bytes (~ %zd mibi bytes)\n",
	     length, length / 1014 / 1024);
    
    m = malloc(length);
    init(m, size);
    free(m, length);

    return EXIT_SUCCESS;
}
