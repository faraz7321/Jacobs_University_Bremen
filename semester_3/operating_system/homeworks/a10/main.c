#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "player.h"

int main(void)
{
  player_t *p;
  char *msg;
  int rc;
  p = player_new();
  if (! p) {
    return EXIT_FAILURE;
  }
  rc = player_get_greeting(p, &msg);
  if (rc > 0) {
    (void) fputs(msg, stdout);
    (void) free(msg);
  }
  while (! (p->state & PLAYER_STATE_FINISHED)) {
    char *line = NULL;
    size_t linecap = 0;
    if (! (p->state & PLAYER_STATE_CONTINUE)) {
      player_fetch_chlng(p);
    }
    rc = player_get_challenge(p, &msg);
    if (rc > 0) {
      (void) fputs(msg, stdout);
      (void) free(msg);
    }
    if (getline(&line, &linecap, stdin) <= 0) {
      break;
    }
    rc = player_post_challenge(p, line, &msg);
    if (rc > 0) {
      (void) fputs(msg, stdout);
      (void) free(msg);
    }
    (void) free(line);
  }
  player_del(p);
  return EXIT_SUCCESS;
}