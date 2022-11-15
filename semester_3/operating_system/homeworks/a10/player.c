/*
 * player.c --
 */

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "player.h"

player_t *player_new()
{
    player_t *p;

    p = malloc(sizeof(player_t));
    if (!p)
    {
        perror("malloc");
        return NULL;
    }
    memset(p, 0, sizeof(*p));
    p->chlng = chlng_new();
    if (!p->chlng)
    {
        free(p);
        return NULL;
    }
    return p;
}

void player_reset(player_t *p)
{
    assert(p);

    p->solved = 0;
    p->total = 0;
    if (p->chlng)
    {
        chlng_reset(p->chlng);
    }
    else
    {
        p->chlng = chlng_new();
    }
}

void player_del(player_t *p)
{
    assert(p);

    if (p->chlng)
    {
        chlng_del(p->chlng);
    }
    free(p);
}

int player_fetch_chlng(player_t *p)
{
    int rc;

    assert(p);
    assert(p->chlng);

    rc = chlng_fetch_text(p->chlng);
    if (rc == 0)
    {
        rc = chlng_hide_word(p->chlng);
    }
    return rc;
}

int player_get_greeting(player_t *p, char **out)
{
    assert(p && out);
    int rc = asprintf(out,
                      "M: Guess the missing ____!\r\n"
                      "M: Send your guess in the form 'R: word\\r\\n'\r\n");

    return rc;
}
int player_get_challenge(player_t *p, char **out)
{
    assert(p && out);
    int rc;

    rc = player_fetch_chlng(p);

    asprintf(out, "C: %s\r\n", p->chlng->text);
    return rc;
}

int player_post_challenge(player_t *p, char *in, char **out)
{
    char *guess;

    assert(p && in && out);

    if (strncmp(in, "Q:", 2) == 0)
    {
        p->state = FINISHED;
        p->finished = true;
        return asprintf(out, "M: You mastered %d/%d challenges. Good bye!\r\n",
                        p->solved, p->total);
    }

    if (strncmp(in, "R: ", 3) != 0)
    {
        p->state = CONTINUE;
        return asprintf(out, "M: Invalid message - ignored.\r\n");
    }

    /* get the guessed word and trim trailing non-alphanumeric characters */
    guess = in + 3;
    for (int i = 0; guess[i]; i++)
    {
        if (!isalpha(guess[i]))
        {
            guess[i] = 0;
            break;
        }
    }

    p->total++;
    if (strcmp(guess, p->chlng->word) != 0)
    {
        p->state = WRONG;
        return asprintf(out, "F: Wrong guess '%s' - expected '%s'\r\n",
                        guess, p->chlng->word);
    }
    else
    {
        p->solved++;
        p->state = GUESSED;
        return asprintf(out, "O: Congratulation - challenge passed!\r\n");
    }
}
