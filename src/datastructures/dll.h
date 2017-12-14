#ifndef __DLL_H_
#define __DLL_H_

#include "data.h"
#include <stdio.h>

typedef struct element {
    container *member;
    struct element *next;
    struct element *prev;
} element;

typedef struct {
    element *head;
    element *tail;
    unsigned int len;
} dll;

dll *new_list();
element *new_element(void *data);
element *new_element_wfree(void *data, void (*free_func) (void *));

void free_element(element *e);
void delete_list(dll *list);
void soft_delete_list(dll *list);

// Basic modification
void push(dll *list, void *data);
void push_wfree(dll *list, void *data, void (*free_func) (void *));
void __push(dll *list, element *new_head);

void append(dll *list, void *data);
void append_wfree(dll *list, void *data, void (*free_func) (void *));
void __append(dll *list, element *new_tail);

void insert(dll *list, void *data, unsigned int index);
void insert_wfree(dll *list, 
                  void *data,
                  unsigned int index,
                  void (*free_func) (void *));
void __insert(dll *list, element *e, unsigned int index);

// Element Removal
element *pop(dll *list);
element *pull(dll *list);
element *remove_element(dll *list, unsigned int index);

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
