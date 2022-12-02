/*
 * scat/scat.c --
 *
 *      An implementation of a simplified version of cat demonstrating
 *      the overhead of system calls relative to library calls and the
 *      benefit one can optain by letting the kernel copy data instead
 *      of letting user space copy data.
 */

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#ifdef __linux__
#include <sys/sendfile.h>
#endif

static int
libcat(void)
{
    int c;
    
    while ((c = getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF) {
            perror("putc");
            return EXIT_FAILURE;
        }
    }
    if (ferror(stdin)) {
        perror("getc");
        return EXIT_FAILURE;
    }
    if (fflush(stdout) == EOF) {
        perror("fflush");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static int
syscat(void)
{
#define WRITE_SIZE      1
    char buffer[WRITE_SIZE];
    ssize_t len, rc;
    
    while ((len = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        rc = write(STDOUT_FILENO, buffer, len);
        if (rc == -1) {
            perror("write");
            return EXIT_FAILURE;
        }
        if (rc != (ssize_t) len) {
            fputs("write: Short write\n", stderr);
            return EXIT_FAILURE;
        }
    }
    if (len == -1) {
        perror("read");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#ifdef __linux__
static int
splicecat(void)
{
    int rc;
#define SPLICE_SIZE 4096
    
    while ((rc = sendfile(STDOUT_FILENO, STDIN_FILENO, 0, SPLICE_SIZE)) > 0) ;
    if (rc == -1) {
        perror("sendfile");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#endif

int
main(int argc, char *argv[])
{
    int opt;
    int (*cat) (void) = libcat;

    while ((opt = getopt(argc, argv, "lsp")) != -1) {
        switch (opt) {
        case 'l':
            cat = libcat;
            break;
        case 's':
            cat = syscat;
            break;
        case 'p':
#ifdef __linux__
            cat = splicecat;
#else
	    fprintf(stderr, "scat: -p not supported, using -l instead\n");
	    cat = libcat;
#endif
            break;
        default:
            fputs("Usage: scat [-l] [-s] [-p]\n", stderr);
            exit(EXIT_FAILURE);
        }
    }

    return cat();
}
