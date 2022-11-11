/*
 * slist/slist.h --
 *
 * This file implements an abstract data type for single linked lists
 * to demonstrate list operations in C. Each node in the list is
 * represented by a C structure which contains a generic data pointer.
 * The generic data pointer can be used to point to whatever the user
 * of this abstract data type wants to organize in a single linked
 * list. The empty list is represented by a NULL pointer, removing the
 * need for a special list head element.
 *
 * Note: The behavior of slist_foreach() is undefined if the function
 * func called for each list element modifies the list itself.
 */

#ifndef _SLIST_H_
#define _SLIST_H_

struct slist {
    void         *data;
    struct slist *next;
};

typedef struct slist slist_t;

inline void*
slist_data(slist_t *list)
{
    return list ? list->data : NULL;
}

inline slist_t*
slist_next(slist_t *list)
{
    return list ? list->next : NULL;
}

extern slist_t*
slist_append(slist_t *list, const void *data);

extern slist_t*
slist_prepend(slist_t *list, const void *data);

extern slist_t*
slist_remove(slist_t *list, const void *data);

extern slist_t*
slist_delete(slist_t *list);

extern int
slist_length(slist_t *list);

extern slist_t*
slist_last(slist_t *list);

extern void
slist_foreach(slist_t *list,
              void (*func) (void *data, void *user), void *user);

extern slist_t*
slist_find(slist_t *list, const void *data);

extern slist_t*
slist_search(slist_t *list,
             int (*cmp) (void *data, void *pattern), void *pattern);

#endif
