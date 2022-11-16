/*
 * chlng.c --
 */

#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <assert.h>
#include "chlng.h"

static char *readall(int fd)
{
    char *result = NULL;
    ssize_t result_len = 0;
    char buf[256];
    ssize_t len;

    while ((len = read(fd, buf, sizeof(buf))) > 0)
    {
        result_len = result_len + len;
        result = realloc(result, result_len + 1);
        if (!result)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        if (result_len == len)
        {
            result[0] = 0;
        }
        strncat(result, buf, len);
    }

    return result;
}

chlng_t *chlng_new()
{
    chlng_t *c;

    c = malloc(sizeof(chlng_t));
    if (!c)
    {
        return NULL;
    }
    c->text = NULL;
    c->word = NULL;
    return c;
}

void chlng_reset(chlng_t *c)
{
    assert(c);

    if (c->text)
        free(c->text);
    if (c->word)
        free(c->word);
    c->text = NULL;
    c->word = NULL;
}

void chlng_del(chlng_t *c)
{
    assert(c);

    if (c->text)
        free(c->text);
    if (c->word)
        free(c->word);
    free(c);
}

int chlng_fetch_text(chlng_t *c)
{
    pid_t pid;
    int fds[2];

    assert(c);
    chlng_reset(c);

    if (pipe(fds) == -1)
    {
        perror("pipe");
        return -1;
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        (void)close(fds[0]);
        (void)close(fds[1]);
        return -2;
    }

    if (pid == 0)
    {
        dup2(fds[1], STDOUT_FILENO);
        (void)close(fds[0]);
        (void)close(fds[1]);
        execlp("fortune", "fortune", "-s", NULL);
        perror("execlp");
        _exit(EXIT_FAILURE);
    }

    close(fds[1]);
    c->text = readall(fds[0]);
    if (c->text)
    {
        for (int i = strlen(c->text) - 1; i >= 0; i--)
        {
            if (!isprint(c->text[i]))
            {
                c->text[i] = 0;
            }
            break;
        }
    }
    close(fds[0]);
    if (strchr(c->text, '\n'))
    {
        return chlng_fetch_text(c);
    }
    return 0;
}

int chlng_hide_word(chlng_t *c)
{
    char *p, *q, *found = NULL;
    int inword;
    int words = 0;

    assert(c);

    for (p = c->text, inword = 0; *p; p++)
    {
        if (isalpha(*p))
        {
            if (!inword)
            {
                inword = 1;
            }
        }
        else
        {
            if (inword)
            {
                words++;
                inword = 0;
            }
        }
    }
    if (inword)
    {
        words++;
    }

    int divisor = RAND_MAX / (words);
    int retval;

    do
    {
        retval = rand() / divisor;
    } while (retval > words);

    for (p = c->text, inword = 0, words = 0; *p; p++)
    {
        if (isalpha(*p))
        {
            if (!inword)
            {
                found = p;
                inword = 1;
            }
        }
        else
        {
            if (inword)
            {
                words++;
                inword = 0;
                if (words == retval)
                {
                    break;
                }
            }
        }
    }

    c->word = strdup(found);
    for (p = found, q = c->word; isalpha(*p); p++, q++)
    {
        *p = '_';
    }
    *q = 0;

    return 0;
}
