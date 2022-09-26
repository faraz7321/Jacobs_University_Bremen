#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

static void usage(void);

int main(int argc, char **argv)
{
    char **ep, *p;
    char *cleanenv[1];
    int ch;

    while ((ch = getopt(argc, argv, "-i")) != -1)
    {
        switch (ch)
        {
        case '-':
        case 'i':
            environ = cleanenv;
            cleanenv[0] = NULL;
            break;
        case '?':
        default:
            usage();
        }
    }

    for (argv += optind; *argv && (p = strchr(*argv, '=')); ++argv)
        (void)putenv(*argv);
    if (*argv)
    {
        execvp(*argv, argv);
        err(errno == ENOENT ? 127 : 126, "%s", *argv);
    }
    for (ep = environ; *ep; ep++)
        (void)printf("%s\n", *ep);
    exit(0);
}

static void usage(void)
{
    fprintf(stderr,
            "usage: env [OPTION]... [NAME=VALUE]... [COMMAND [ARG]...]\n");
    exit(1);
}
