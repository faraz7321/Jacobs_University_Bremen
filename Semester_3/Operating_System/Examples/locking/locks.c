/*
 * locking/locks.c --
 *
 *	Demonstration of POSIX advisory locks using the fcntl API.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "locks.h"

int lock_file_read(int fd, off_t start, off_t len)
{
    struct flock fl;
    int rc;

    memset(&fl, 0, sizeof(fl));
    fl.l_type = F_RDLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = start;
    fl.l_len = len;
    rc = fcntl(fd, F_SETLKW, &fl);	/* potentially wait for the lock */
    if (rc == -1) {
	perror("fcntl");
    }
    return rc;
}

int lock_file_write(int fd, off_t start, off_t len)
{
    struct flock fl;
    int rc;

    memset(&fl, 0, sizeof(fl));
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = start;
    fl.l_len = len;
    rc = fcntl(fd, F_SETLKW, &fl);	/* potentially wait for the lock */
    if (rc == -1) {
	perror("fcntl");
    }
    return rc;
}

int unlock_file(int fd, off_t start, off_t len)
{
    struct flock fl;
    int rc;

    memset(&fl, 0, sizeof(fl));
    fl.l_type = F_UNLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = start;
    fl.l_len = len;
    rc = fcntl(fd, F_SETLK, &fl);
    if (rc) {
	perror("fcntl");
    }
    return rc;
}
