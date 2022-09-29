/*
 * cat++/cat++.c
 *
 *	Copy multiple files to the standard output. Note that the
 *      special file name "-" is interpreted to mean stdin and may
 *      appear multiple times. This version checks for errors on the
 *      stdout stream and supports dynamically loadable transforms.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

static const char progname[] = "cat++";

typedef char *(transfunc)(char *line);

typedef struct {
    void *handle;
    transfunc *transform;
} transform_t;

static int
cat(const char *filename, transform_t *transforms)
{
    int i;
    FILE *in;
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

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

    while ((linelen = getline(&line, &linecap, in)) > 0) {
	if (line[0] != '\0' || !feof(in)) {
	    if (line[linelen-1] == '\n') {
		line[linelen-1] = 0;
	    }
	    for (i = 0; transforms[i].handle; i++) {
		line = (*transforms[i].transform)(line);
	    }
	    puts(line);
	}
    }
    if (line) {
	free(line);
    }

    if (fflush(stdout) || ferror(stdout) || ferror(in)) {
	perror(progname);
	exit(EXIT_FAILURE);
    }
    
    if (in != stdin) {
	fclose(in);
    }

    return 0;
}

int
main(int argc, char *argv[])
{
    int c, t = 0;
    int code = EXIT_SUCCESS;
    char *error;

    transform_t transforms[argc];
    memset(transforms, 0, argc * sizeof(transform_t));

    while ((c = getopt(argc, argv, "hlv")) >= 0) {
	switch (c) {
	case 'h':
	    printf("Usage: %s [-h] [-l transform] [-v] files ... \n",
		   progname);
	    return EXIT_SUCCESS;
	case 'l':
	    (void) dlerror();
	    transforms[t].handle = dlopen(argv[optind++], RTLD_LAZY);
	    if (! transforms[t].handle) {
		fprintf(stderr, "%s: %s\n", progname, dlerror());
		return EXIT_FAILURE;
	    }
	    (void) dlerror();
	    /*
	     * C99 does not allow to convert between a data pointer
	     * (void *) and a function pointer but the dlsym function
	     * expects you to do just that. So we have to tell GCC to
	     * not be pedantic about this conversion...
	     */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
	    transforms[t].transform = (transfunc *) dlsym(transforms[t].handle, "transform");
#pragma GCC diagnostic pop
	    if ((error = dlerror()) != NULL)  {
		fprintf(stderr, "%s: %s\n", progname, error);
		return EXIT_FAILURE;
	    }
	    t++;
	    break;
	case 'v':
	    printf("%s version 0.1.0\n", progname);
	    return EXIT_SUCCESS;
	default:
	    return EXIT_FAILURE;
	}
    }

    if (optind == argc) {
	if (cat(NULL, transforms) < 0) {
	    code = EXIT_FAILURE;
	}
    } else {
	for (; optind < argc; optind++) {
	    if (cat(argv[optind], transforms) < 0) {
		code = EXIT_FAILURE;
	    }
	}
    }

    for (t = 0; transforms[t].handle; t++) {
	(void) dlclose(transforms[t].handle);
    }

    return code;
}
