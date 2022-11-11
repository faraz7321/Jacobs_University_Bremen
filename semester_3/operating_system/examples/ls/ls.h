/*
 * ls/ls.h --
 *
 */

#ifndef LS_H
#define LS_H

#include <dirent.h>

#define LS_FLAG_ALL	0x01
#define LS_FLAG_LONG	0x02
#define LS_FLAG_NUMERIC 0x04

extern void show(struct dirent *e, int flags);
extern void ls(const char *directory, int flags);

#endif
