/*
 * snake/dlist.c --
 *
 *	Implementation of the doubly linked list abstract data type.
 */

#include <stdlib.h>
#include "dlist.h"

extern void* dlist_data(dlist_t *list);
extern dlist_t* dlist_next(dlist_t* list, dlist_t* p);
extern dlist_t* dlist_prev(dlist_t* list, dlist_t* p);

static inline dlist_t*
dlist_new(const void *data)
{
    dlist_t *p;

    p = malloc(sizeof(dlist_t));
    if (! p) {
        exit(EXIT_FAILURE);
    }
    p->data = (void *) data;
    p->next = p->prev = p;
    return p;
}

dlist_t*
dlist_prepend(dlist_t *list, const void *data)
{
    dlist_t *p;

    p = dlist_new(data);
    if (! list) {
        return p;
    } 
    p->prev = list->prev, list->prev->next = p;
    p->next = list, list->prev = p;
    return p;
}

dlist_t*
dlist_append(dlist_t *list, const void *data)
{
    dlist_t *p;

    p = dlist_new(data);
    if (! list) {
        return p;
    } 
    p->prev = list->prev, list->prev->next = p;
    p->next = list, list->prev = p;
    return list;
}

dlist_t*
dlist_remove(dlist_t *list, const void *data)
{
    dlist_t *p, *q;

    for (p = list; p; ) {
        if (p->data == data) {
            if (p->next == p && p->prev == p) {
                free(p);
                list = p = NULL;
            } else {
                q = p;
                p->prev->next = p->next;
                p->next->prev = p->prev;
                p = dlist_next(list, p->prev);
                if (q == list) list = p;
                free(q);
            }
        } else {
            p = dlist_next(list, p);
        }
    }
    return list;
}

dlist_t*
dlist_delete(dlist_t *list)
{
    dlist_t *p, *q;

    for (p = list; p; ) {
        q = p, p = dlist_next(list, p), free(q);
    }
    return NULL;
}

int
dlist_length(dlist_t *list)
{
    dlist_t *p;
    int l = 0;

    for (p = list; p; p = dlist_next(list, p)) l++;
    return l;
}

dlist_t*
dlist_last(dlist_t *list)
{
    return (list ? list->prev : NULL); 
}

void
dlist_foreach(dlist_t *list,
              void (*func) (void *data, void *user), void *user)
{
    dlist_t *p;

    if (func) {
        for (p = list; p; p = dlist_next(list, p)) {
            func((p)->data, user);
        }
    }
}

dlist_t*
dlist_find(dlist_t *list, const void *data)
{
    dlist_t *p;
    
    for (p = list; p; p = dlist_next(list, p)) {
        if (p->data == data) {
            return p;
        }
    }
    return NULL;
}

dlist_t*
dlist_search(dlist_t *list,
             int (*cmp) (void *data, void *pattern), void *pattern)
{
    dlist_t *p;

    if (cmp) {
        for (p = list; p; p = dlist_next(list, p)) {
            if (cmp(p->data, pattern) == 0) {
                return p;
            }
        }
    }
    return NULL;
}
