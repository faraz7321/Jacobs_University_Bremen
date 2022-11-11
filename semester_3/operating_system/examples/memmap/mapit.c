/*
 * memmap/mapit.c --
 *
 *      The mapit() function allocates memory using mmap().
 */

#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#define _DARWIN_C_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "memmap.h"

void mapit(int flags)
{
    unsigned char *p;
    long pagesize, length;
    
    pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }

    length = 10 * pagesize;                     /* 10 pages - why 10? */
    pmap("after main() is called", flags);
    
    p = mmap(NULL, length, PROT_READ | PROT_WRITE,
             MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    pmap("after calling mmap()", flags);

    if (flags & MEMMAP_L_FLAG) {                /* lock the pages */
        if (mlock(p, length) == -1) {
            perror("mlock");
            exit(EXIT_FAILURE);
        }
        pmap("after calling mlock()", flags);
    }

    p[0] = 0xff;                                /* dirty the first page */
    pmap("after writing p[0]", flags);

    p[length-1] = 0xff;                         /* dirty the last page */
    pmap("after writing p[length-1]", flags);
    
    if (munmap(p, length) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
    pmap("after calling munmap()", flags);
}

