/*
 * slist/slist.c --
 *
 * Implementation of the single linked list abstract data type.
 */

#include <stdlib.h>
#include "slist.h"

extern void* slist_data(slist_t *list);
extern slist_t* slist_next(slist_t *list);

static inline slist_t*
slist_new(const void *data, slist_t *next)
{
    slist_t *p;

    p = malloc(sizeof(slist_t));
    if (! p) {
        exit(EXIT_FAILURE);
    }
    p->data = (void *) data;
    p->next = next;
    return p;
}

slist_t*
slist_prepend(slist_t *list, const void *data)
{
    return slist_new(data, list);
}

slist_t*
slist_append(slist_t *list, const void *data)
{
    slist_t *p;

    if (! list) {
        list = slist_new(data, NULL);
    } else {
        p = slist_last(list);
        p->next = slist_new(data, NULL);
    }
    return list;
}

slist_t*
slist_remove(slist_t *list, const void *data)
{
    slist_t *p, *q;

    for (p = list, q = NULL; p; ) {
        if (p->data == data) {
            if (q) {
                q->next = p->next;
                free(p);
                p = q->next;
            } else {
                list = p->next;
                free(p);
                p = list;
            }
        } else {
            q = p, p = p->next;
        }
    }
    return list;
}

slist_t*
slist_delete(slist_t *list)
{
    slist_t *p, *q;

    for (p = list; p; ) {
        q = p, p = p->next, free(q);
    }
    return NULL;
}

int
slist_length(slist_t *list)
{
    slist_t *p;
    int l;

    for (p = list, l = 0; p; p = p->next) l++;
    return l;
}

slist_t*
slist_last(slist_t *list)
{
    slist_t *p;

    for (p = list; p->next; p = p->next) ;
    return p;
}

void
slist_foreach(slist_t *list,
              void (*func) (void *data, void *user), void *user)
{
    slist_t *p;

    if (func) {
        for (p = list; p; p = p->next) {
            func(p->data, user);
        }
    }
}

slist_t*
slist_find(slist_t *list, const void *data)
{
    slist_t *p;
    
    for (p = list; p; p = p->next) {
        if (p->data == data) {
            return p;
        }
    }
    return NULL;
}

slist_t*
slist_search(slist_t *list,
             int (*cmp) (void *data, void *pattern), void *pattern)
{
    slist_t *p;

    if (cmp) {
        for (p = list; p; p = p->next) {
            if (cmp(p->data, pattern) == 0) {
                return p;
            }
        }
    }
    return NULL;
}
