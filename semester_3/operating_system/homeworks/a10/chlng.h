/*
 * chlng.h --
 */

#ifndef CHLNG_H
#define CHLNG_H

typedef struct {
    char *text;                 /* text with a missing word */
    char *word;                 /* the missing word */
} chlng_t;

/* Allocate a new challenge. */
extern chlng_t* chlng_new();

/* Reset the internal state of the challenge. */
extern void chlng_reset(chlng_t*);

/* Delete a challenge and all its resources. */
extern void chlng_del(chlng_t*);

/* Fetch new text from an invocation of 'fortune'. */
extern int chlng_fetch_text(chlng_t *c);

/* Select and hide a word in the text. */
extern int chlng_hide_word(chlng_t *c);

#endif
