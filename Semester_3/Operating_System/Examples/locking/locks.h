/*
 * locking/locks.h --
 *
 *	Demonstration of POSIX advisory locks using the fcntl API.
 */

#define _POSIX_C_SOURCE 201112L

#ifndef _LOCKS_H
#define _LOCKS_H

extern int lock_file_read(int fd, off_t start, off_t len);
extern int lock_file_write(int fd, off_t start, off_t len);
extern int unlock_file(int fd, off_t start, off_t len);

#endif
