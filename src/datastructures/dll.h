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

// Primitive factories for list generation
dll *list_from_ints(int *array, unsigned int len);

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
void *pop(dll *list);
void *pull(dll *list);
void *remove_element(dll *list, unsigned int index);
element *__remove_element(dll *list, unsigned int index);

// View elements
void *view_first(dll *list);
void *view_last(dll *list);
void *view_at(dll *list, unsigned int index);
element *__view_at(dll *list, unsigned int index);

// Join
dll *concat(dll *dest, dll *src);
dll *shuffle(dll *dest, dll *src);
dll *merge_union(dll *list1, dll *list2);

// Copy Lists
dll *copy_list(dll *src);
dll *deep_copy(dll *src);

long diff(dll *list1, dll *list2, long (*compar) (void *, void *));
#endif
