/*
 * memmap/memmap.c --
 *
 *      This program demonstrates how to allocate memory using
 *      anonymous memory mappings. It also shows how information
 *      about memory mappings can be found on Linux systems.
 */

#define _POSIX_C_SOURCE 200809L

#define _DEFAULT_SOURCE
#define _DARWIN_C_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#define MEMMAP_L_FLAG 0x1
#define MEMMAP_V_FLAG 0x2

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

void mapit(int flags);
void pmap(const char *msg, int flags);

static const char *progname = "memmap";

int main(int argc, char *argv[])
{
    int c;
    int flags = 0;

    while ((c = getopt(argc, argv, "lvh")) >= 0)
    {
        switch (c)
        {
        case 'l':
            flags |= MEMMAP_L_FLAG;
            break;
        case 'v':
            flags |= MEMMAP_V_FLAG;
            break;
        case 'h':
            printf("Usage: %s [-l] [-v]\n", progname);
            return EXIT_SUCCESS;
        }
    }

    mapit(flags);
    return EXIT_SUCCESS;
}
void pmap(const char *msg, int flags)
{
    char cmd[1234];

    if (flags & MEMMAP_V_FLAG)
    {
        if (msg)
        {
            printf("\n===> %s:\n", msg);
            fflush(stdout);
        }
        snprintf(cmd, sizeof(cmd), "pmap -x %d", getpid());
        system(cmd);
    }
}
void mapit(int flags)
{
    unsigned char *p;
    long pagesize, length;

    pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1)
    {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }

    length = 10 * pagesize; /* 10 pages - why 10? */
    pmap("after main() is called", flags);

    p = mmap(NULL, length, PROT_READ | PROT_WRITE,
             MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (p == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    pmap("after calling mmap()", flags);

    if (flags & MEMMAP_L_FLAG)
    { /* lock the pages */
        if (mlock(p, length) == -1)
        {
            perror("mlock");
            exit(EXIT_FAILURE);
        }
        pmap("after calling mlock()", flags);
    }

    p[0] = 0xff; /* dirty the first page */
    pmap("after writing p[0]", flags);

    p[length - 1] = 0xff; /* dirty the last page */
    pmap("after writing p[length-1]", flags);

    if (munmap(p, length) == -1)
    {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
    pmap("after calling munmap()", flags);
}
