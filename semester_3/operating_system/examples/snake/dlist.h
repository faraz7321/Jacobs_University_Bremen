/*
 * snake/dlist.h --
 *
 *	This file implements an abstract data type for doubly linked
 *	lists to demonstrate list operations in C. Each node in the
 *	list is represented by a C structure which contains a generic
 *	data pointer.  The generic data pointer can be used to point
 *	to whatever the user of this abstract data type wants to
 *	organize in a double linked list.
 */

#ifndef _DLIST_H_
#define _DLIST_H_

struct dlist {
    void         *data;
    struct dlist *next;
    struct dlist *prev;
};

typedef struct dlist dlist_t;

inline void*
dlist_data(dlist_t *list)
{
    return list ? list->data : NULL;
}

inline dlist_t*
dlist_next(dlist_t* list, dlist_t* p)
{
    return (list && p && p->next != list) ? p->next : NULL;
}

inline dlist_t*
dlist_prev(dlist_t* list, dlist_t* p)
{
    return (list && p && p != list) ? p->prev : NULL;
}

extern dlist_t*
dlist_append(dlist_t *list, const void *data);

extern dlist_t*
dlist_prepend(dlist_t *list, const void *data);

extern dlist_t*
dlist_remove(dlist_t *list, const void *data);

extern dlist_t*
dlist_delete(dlist_t *list);

extern int
dlist_length(dlist_t *list);

extern dlist_t*
dlist_last(dlist_t *list);

extern void
dlist_foreach(dlist_t *list,
              void (*func) (void *data, void *user), void *user);

extern dlist_t*
dlist_find(dlist_t *list, const void *data);

extern dlist_t*
dlist_search(dlist_t *list,
             int (*cmp) (void *data, void *pattern), void *pattern);

#endif
