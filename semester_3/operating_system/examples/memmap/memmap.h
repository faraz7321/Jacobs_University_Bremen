/*
 * memmap/memmap.h --
 *
 *      This program demonstrates how to allocate memory using
 *      anonymous memory mappings. It also shows how information
 *      about memory mappings can be found on Linux systems.
 */

#ifndef MEMMAP_H
#define MEMMAP_H

#define MEMMAP_L_FLAG 0x1
#define MEMMAP_V_FLAG 0x2

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

extern void mapit(int flags);
extern void pmap(const char *msg, int flags);

#endif
