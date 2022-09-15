/*
 * Faraz Ahmad fa.ahmad@jacobs-university.de
 * CO-562 Operating Systems
 * p1_a3
 * env.c
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// Function Declaration
void printEnv();
void unset(char *);
void newEnv();
bool addVar(char *);

/* environ is defined as a global variable
in the Glibc source file posix/environ.c*/
extern char **environ;

int main(int argc, char *argv[])
{
    int opt;

    while ((opt = getopt(argc, argv, "-:i0u:v")) != -1)
    {
        switch (opt)
        {
        case '?':
        {
            printf("Unknown Command!\n");
            _exit(0);
            break;
        }
        case ':':
        {
            printf("Missing argument!\n");
            _exit(0);
            break;
        }
        case 'i':
        {
            newEnv();
            break;
        }

        case 'u':
        {
            unset(optarg);
            break;
        }

        case 'v':
        {
            printEnv();
            break;
        }

        case 1:
        {
            if (!addVar(optarg))
            {
                printf("err\n");
                _exit(0);
            }
            break;
        }
        }
    }
    printEnv();
    return 0;
}

void printEnv()
{
    for (int i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
}

void unset(char *name)
{
    char *c;
    int j;
    for (int i = 0; environ[i] != NULL; i++)
    {
        if ((c = strstr(environ[i], name)) != NULL)
        {
            for (j = i; environ[j + 1] != NULL; j++)
            {
                environ[j] = environ[j + 1];
            }
            environ[j] = NULL;
            break;
        }
    }
}

void newEnv()
{
    for (int i = 0; environ[i] != NULL; i++)
    {
        environ[i] = NULL;
    }
}

bool addVar(char *var)
{
    int i;

    if (strstr(var, "="))
    {
        for (i = 0; environ[i] != NULL; i++)
        {
            continue;
        }
        environ[i] = var;
        environ[i + 1] = NULL;
        return true;
    }
    else
    {
        return false;
    }
}