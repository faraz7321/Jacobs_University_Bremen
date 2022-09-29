/*
 * hello-write.c --
 *
 *      This program invokes the Linux write() system call.
 *
 * Exercise:
 *
 * Statically Compile and run the program. Look at the assembler code
 * generated (objdump -S, or gcc -S).
 */
  
#include <stdlib.h>
#include <unistd.h>

int
main(void)
{
    const char msg[] = "Hello World\n";
    ssize_t n;

    n = write(STDOUT_FILENO, msg, sizeof(msg));
    if (n == -1 || n != sizeof(msg)) {
        const char err[] = "write system call failed\n";
        (void) write(STDERR_FILENO, err, sizeof(err));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
