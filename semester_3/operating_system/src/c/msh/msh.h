/*
 * msh/msh.h --
 *
 *	This file contains common definitions for msh.
 */

#ifndef _MSH_H
#define _MSH_H

#include <stdio.h>

extern const char *progname;

extern void msh_show_prompt(void);

extern void msh_read_command(FILE *stream, int *argc, char ***args);

#endif
