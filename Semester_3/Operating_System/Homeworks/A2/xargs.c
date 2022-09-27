#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define _PATH_ECHO "/bin/echo"

static void usage(void);

static char ch;
extern char **environ;

int main(int argc, char *argv[])
{
    while ((ch = getopt(argc, argv, "0E:j:n:tx")) != -1)
    {
        switch (ch)
        {
        case 'n':
        {
            break;
        }
        case 't':
        {
            break;
        }
        case 'j':
        {
            break;
        }
        case '0':
        {
            break;
        }
        case '?':
        {
            break;
        }
        default:
        {
            usage();
        }
        }
    }
}

static void usage(void)
{
    fprintf(stderr,
            "Usage: xargs [OPTION]... COMMAND [INITIAL-ARGS]...\n"
            "Run COMMAND with arguments INITIAL-ARGS and more arguments read from input.\n"
            "Mandatory and optional arguments to long options are also\n"
            "mandatory or optional for the corresponding short option.\n"
            "\n-n, --max-args=MAX-ARGS      use at most MAX-ARGS arguments per command line\n"
            "\n-t, --verbose                print commands before executing them\n"
            "\n-j                           the (maximum) number of processes (jobs) executed\n"
            "                               concurrently (default is 1, which means processes\n"
            "                               are executed sequentially)\n");
    exit(1);
}
//fork()
//execvp()
//waitpid()
//getopt()
//getline()
