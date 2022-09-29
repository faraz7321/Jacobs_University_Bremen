/*
 * hello-writev.c --
 *
 *      This program which invokes the Linux writev() system call,
 *      which is useful if the data to be written is stored at
 *      different memory locations.
 */
  
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/uio.h>

int
main(void)
{
    struct iovec iov[2];
    ssize_t n;

    iov[0].iov_base = "Hello ";
    iov[0].iov_len = strlen(iov[0].iov_base);
    iov[1].iov_base = "World\n";
    iov[1].iov_len = strlen(iov[1].iov_base);

    n = writev(STDOUT_FILENO, iov, 2);
    if (n == -1 || (size_t) n != iov[0].iov_len + iov[1].iov_len) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
