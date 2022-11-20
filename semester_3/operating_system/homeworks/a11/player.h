/*
 * player.h --
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "chlng.h"

enum PLAYER_STATE
{
    NEW = 0,
    WRONG = 1,
    GUESSED = 2,
    CONTINUE = 4,
    FINISHED = 8
};

typedef struct player
{
    int state;  /* current state of the player */
    int solved; /* correctly solved challenges */
    int total;  /* total number of challenges */
    // bool finished;  /* true if we are done */
    chlng_t *chlng; /* current challenge */
} player_t;

/* Allocate a new player. */
extern player_t *player_new();

/* Reset the internal state of the player. */
extern void player_reset(player_t *);

/* Delete a player and all its resources. */
extern void player_del(player_t *);

/* Allocate a new challenge for the player. */
extern int player_fetch_chlng(player_t *);

/* Retrieve a greeting message. */
extern int player_get_greeting(player_t *, char **);

/* Retrieve the challenge message. */
extern int player_get_challenge(player_t *, char **);

/* Post a message to the player and retrieve the response message. */
extern int player_post_challenge(player_t *, char *, char **);

#endif
