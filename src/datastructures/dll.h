#ifndef __DLL_H_
#define __DLL_H_

#include "data.h"

typedef struct {
    container *data;
    struct element *next;
    struct element *prev;
} element;

typedef struct {
    element *head;
    element *tail;
    unsigned int len;
} dll;

dll *new_list();
void delete_list(dll *list);
void soft_delete_list(dll *list);

// Basic modification
void push(dll *list, element *data);
void append(dll *list, element *data);
void insert(dll *list, element *data, unsigned int index);

// Element Removal
element *pop(dll *list);
element *pull(dll *list);
element *remove(dll *list, unsigned int index);

// View elements
element *view_first(dll *list);
element *view_last(dll *list);
element *view_at(dll *list, unsigned int index);

// Join
dll *concat(dll *dest, dll *src);
dll *shuffle(dll *dest, dll *src);
dll *merge_union(dll *list1, dll *list2);

long diff(dll *list1, dll *list2, long (*compar) (void *, void *));
#endif
