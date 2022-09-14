/*
 * hello-syscall.c --
 *
 * This program invokes the Linux write() system call by using
 * the generic syscall library function.
 */
#define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <syscall.h>

int main(void)
{
    const char msg[] = "Hello World\n";
    ssize_t n;

    n = syscall(SYS_write, 1, msg, sizeof(msg));
    if (n == -1 || n != sizeof(msg))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
