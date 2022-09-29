/*
 * cat/cat.c --
 *
 *	Copy multiple files to the standard output. Note that the
 *	special file name "-" is interpreted to mean stdin and may
 *	appear multiple times. This version checks for errors on the
 *	stdout stream and uses memory mapped I/O on regular files,
 *	which makes a significant difference on large files.
 */

#define _POSIX_C_SOURCE 2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <assert.h>

static const char progname[] = "cat";

static int
cat(const char *filename)
{
    FILE *in;
    int c;

    if (! filename || strcmp(filename, "-") == 0) {
        clearerr(stdin);
        in = stdin;
    } else {
        in = fopen(filename, "r");
        if (! in) {
            perror(progname);
            return -1;
        }
    }

    while ((c = getc(in)) != EOF) {
        putc(c, stdout);
    }
    
    if (fflush(stdout) || ferror(stdout) || ferror(in)) {
        perror(progname);
        return -1;
    }

    if (in != stdin) {
        fclose(in);
    }

    return 0;
}

static int
mcat(const char *filename)
{
    int status, fd;
    char *base, *p;
    struct stat buf;
    ssize_t n, len;

    if (! filename || strcmp(filename, "-") == 0) {
        return cat(filename);
    }

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror(progname);
        return -1;
    }

    if (fstat(fd, &buf) == -1 || ! S_ISREG(buf.st_mode)) {
        close(fd);
        return cat(filename);
    }

    base = mmap(0, buf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (base == MAP_FAILED) {
        close(fd);
        return cat(filename);
    }

    for (p = base, len = buf.st_size;
         len; len -= n, p += n) {
        n = write(fileno(stdout), p, len);
        if (n == -1) {
            perror(progname);
            exit(1);
        }
    }

    status = munmap(base, buf.st_size);
    assert(status == 0);
    close(fd);

    return 0;
}

int
main(int argc, char *argv[])
{
    int c, status = EXIT_SUCCESS;
    int (*vcat)(const char *filename) = cat;

    while ((c = getopt(argc, argv, "hmv")) >= 0) {
        switch (c) {
        case 'h':
            printf("Usage: %s [-h] [-m] [-v] files ... \n", progname);
            return EXIT_SUCCESS;
        case 'm':
            vcat = mcat;
            break;
        case 'v':
            printf("%s version 0.3.0\n", progname);
            return EXIT_SUCCESS;
        default:
            return EXIT_FAILURE;
        }
    }

    if (optind == argc) {
        if (vcat(NULL) < 0) {
            status = EXIT_FAILURE;
        }
    } else {
        for (; optind < argc; optind++) {
            if (vcat(argv[optind]) < 0) {
                status = EXIT_FAILURE;
            }
        }
    }

    return status;
}
