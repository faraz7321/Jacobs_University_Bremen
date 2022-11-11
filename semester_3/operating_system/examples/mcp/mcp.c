/*
 * mcp/mcp.c --
 *
 *	This program uses memory mapped I/O to create a copy of a
 *	regular file. It does not aim to handle non-regular files.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

static const char *progname = "mcp";

static void
fail2(char *msg1, char *msg2)
{
    fprintf(stderr, "%s: %s: %s: %s\n", progname, msg1, msg2, strerror(errno));
    exit(EXIT_FAILURE);
}

static void
fail1(char *msg)
{
    fprintf(stderr, "%s: %s: %s\n", progname, msg, strerror(errno));
    exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
    int fdin, fdout;
    void *src, *dst;
    struct stat statbuf;

    if (argc != 3) {
	fprintf(stderr, "%s: usage: %s <srcfile> <dstfile>\n",
		progname, progname);
	return EXIT_FAILURE;
    }

    fdin = open(argv[1], O_RDONLY);
    if (fdin < 0) {
        fail2("open", argv[1]);
    }

    /*
     * Obtain the source file size in order to create a destination
     * file of the same size (by seeking towards the end and writing a
     * single byte). We also use the source file's permission for
     * setting up the permissions on the destination file.
     */

    if (fstat(fdin, &statbuf) < 0) {
        fail1("fstat");
    }
    if (! S_ISREG(statbuf.st_mode)) {
	fprintf(stderr, "%s: %s: not a regular file\n", progname, argv[1]);
	return EXIT_FAILURE;
    }

    fdout = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, statbuf.st_mode);
    if (fdout < 0) {
        fail2("open", argv[2]);
    }
    if (lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1) {
        fail1("lseek");
    }
    if (write (fdout, "", 1) != 1) {
        fail1("write");
    }

    src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0);
    if (src == MAP_FAILED) {
        fail1("mmap");
    }

    dst = mmap(0, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fdout, 0);
    if (dst == MAP_FAILED) {
        fail1("mmap");
    }
    
    memcpy(dst, src, statbuf.st_size);

    if (munmap(dst, statbuf.st_size) == -1) {
        fail1("munmap");
    }
    if (munmap(src, statbuf.st_size) == -1) {
        fail1("munmap");
    }
    (void) close(fdin);
    (void) close(fdout);

    return EXIT_SUCCESS;
}

