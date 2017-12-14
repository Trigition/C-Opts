#include "dll.h"

/**
 * @brief This function allocates a new list
 */
dll *new_list() {
    // Allocate memory
    dll *list = (dll *) malloc(sizeof(dll));
    if (list == NULL) {
        printf("Error allocating list\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->len = 0;

    return list;
}

/**
 * @brief This function allocates a new element
 * using the stdlib free as the free function.
 */
element *new_element(void *data) {
    container *data_container = new_container(data, &free);
    element *data_element = (element *) malloc(sizeof(element));

    data_element->member = data_container;
    data_element->next = NULL;
    data_element->prev = NULL;

    return data_element;
}

element *new_element_wfree(void *data, void (*free_func) (void *)) {
    container *data_container = new_container(data, free_func);
    element *data_element = (element *) malloc(sizeof(element));

    data_element->member = data_container;
    data_element->next = NULL;
    data_element->prev = NULL;

    return data_element;
}

/**
 * @brief This function frees an element and its data
 */
void free_element(element *e) {
    container *e_container = e->member;
    e_container->free_func(e_container->data);
    free(e_container);
    free(e);
}

/**
 * @brief This function frees a list and its data
 */
void delete_list(dll *list) {
    element *cur_element = list->head;
    element *prev_element = list->head;
    for (unsigned int i = 0; i < list->len; i++) {
        cur_element = cur_element->next;
        free_element(prev_element);
        prev_element = cur_element;
    }
    free(list);
}

/**
 * @brief This function frees a list without affecting its
 * contained data.
 */
void soft_delete_list(dll *list) {
    element *cur_element = list->head;
    element *prev_element = list->head;
    for (unsigned int i = 0; i < list->len; i++) {
        cur_element = cur_element->next;
        free(cur_element);
        prev_element = cur_element;
    }
    free(list);
}

void push(dll *list, void *data) {
    element *new_head = new_element(data);

    __push(list, new_head);
}

void push_wfree(dll *list, void *data, void (*free_func) (void *)) {
    element *new_head = new_element_wfree(data, free_func);

    __push(list, new_head);
}

void __push(dll *list, element *new_head) {
    element *old_head = list->head;
    
    old_head->prev = new_head;
    new_head->next = old_head;
    list->head = new_head;
    list->len++;
}

void append(dll *list, void *data) {
    element *new_tail = new_element(data);

    __append(list, new_tail);
}

void append_wfree(dll *list, void *data, void (*free_func) (void *)) {
    element *new_tail = new_element_wfree(data, free_func);

    __append(list, new_tail);
}

void __append(dll *list, element *new_tail) {
    element *old_tail = list->tail;

    old_tail->next = new_tail;
    new_tail->prev = old_tail;
    list->tail = new_tail;
    list->len++;
}

void __insert(dll *list, element *e, unsigned int index) {
    // Check bounds of index specification
    if (index == 0) {
        
    }
}
