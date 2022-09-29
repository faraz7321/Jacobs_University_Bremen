/*
 * locking/main.c --
 *
 *	Demonstration of POSIX advisory locks using the fcntl API.
 *
 *      The program options tell what needs to be done (odd design,
 *      it would be better to read commands from stdin):
 *       -o file # open file
 *       -r      # acquire a read lock on the open file
 *       -w      # acquire a write lock on the open file
 *       -u      # release a lock
 *       -c      # close the open file
 *       -s num  # set the start to num
 *       -l num  # set the len to num
 *       -v      # show the list of locks on the system
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "locks.h"

static int
open_file(const char *name)
{
    int fd;

    fd = open(name, O_RDWR);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    return fd;
}

static int
close_file(int fd)
{
    int rc;
    
    rc = close(fd);
    if (rc == -1) {
        perror("close");
        return fd;
    }
    return -1;
}

int
main(int argc, char *argv[])
{
    int c, fd = -1;
    off_t start = 0;
    off_t len = 0;

    while ((c = getopt(argc, argv, "o:cs:l:rwuv")) != -1) {
        switch (c) {
        case 'o':
            fd = open_file(optarg);
            break;
        case 'c':
            fd = close_file(fd);
            break;
        case 'l':
            len = atoi(optarg);
            break;
        case 's':
            start = atoi(optarg);
            break;
        case 'r':
            lock_file_read(fd, start, len);
            break;
        case 'w':
            lock_file_write(fd, start, len);
            break;
        case 'u':
            unlock_file(fd, start, len);
            break;
        case 'v':
            (void) system("lslocks");
            break;
	default:
	    fprintf(stderr, "usage: locking -o file -c -s start -l len -r -w -u -v\n");
	    return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
