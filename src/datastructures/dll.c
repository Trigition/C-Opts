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

/**
 * @brief This function allocates a new element 
 * with a custom free function for its data.
 * @param data The data to be encapsulated.
 * @param free_func A free function for the data. Must take
 * the data as a void pointer.
 * @return The allocated element.
 */
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
        free(prev_element);
        prev_element = cur_element;
    }
    free(list);
}

/**
 * @brief This function puts data to the front of the list.
 * @param data The data to be placed (it is encapsulated within
 * a list element).
 */
void push(dll *list, void *data) {
    element *new_head = new_element(data);

    __push(list, new_head);
}

/**
 * @brief This function puts data to the front of the list with a custom
 * free function.
 * @param data The data to be encapsulated.
 * @param free_func The free function for the data.
 */
void push_wfree(dll *list, void *data, void (*free_func) (void *)) {
    element *new_head = new_element_wfree(data, free_func);

    __push(list, new_head);
}

/**
 * @brief This function pushes an element to the front of the list.
 * @param list The list to be altered.
 */
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

void insert(dll *list, void *data, unsigned int index) {
    element *e = new_element(data);

    __insert(list, e, index);
}

void insert_wfree(dll *list, void *data, unsigned int index, void (*free_func) (void *)) {
    element *e = new_element_wfree(data, free_func);

    __insert(list, e, index);
}

void __insert(dll *list, element *e, unsigned int index) {
    // Check bounds of index specification
    if (index == 0) {
        // We're just pushing to the front of the list
        __push(list, e);
        return;
    } else if (index == list->len) {
        // We're appending to the end of the list
        __append(list, e);
        return;
    } else if (index > list->len) {
        // Range specified is beyond range of current list
        return;
    }
    // Range falls somewhere within the bounds of the list
    element *prev_ele = __view_at(list, index - 1);
    element *next_ele = prev_ele->next;

    // Insert
    e->next = next_ele;
    e->prev = prev_ele;
    next_ele->prev = e;
    prev_ele->next = e;
    list->len++;
}

element *__remove_element(dll *list, unsigned int index) {
    element *element_to_remove = __view_at(list, index);
    element *prev_element = element_to_remove->prev;
    element *next_element = element_to_remove->next;

    // Bounds check
    if (index >= list->len) {
        return NULL;
    }
    if (prev_element == list->tail && next_element == list->head) {
        // Only element in list
        list->len--;
        list->head = NULL;
        list->tail = NULL;
        return element_to_remove;
    } else if (prev_element == list->head) {
        // Head of list
        list->head = next_element;
        next_element->prev = list->head->prev;
        list->len--;
        return element_to_remove;
    } else if (next_element == list->tail) {
        // Tail of list
        list->tail = prev_element;
        prev_element->next = list->tail->next;
        return element_to_remove;
    } else {
        // Somewhere in the middle of the list
        prev_element->next = next_element;
        next_element->prev = prev_element;
        element_to_remove->next = NULL;
        element_to_remove->prev = NULL;
        list->len--;

        return element_to_remove;
    }
}

void *view_first(dll *list) {
    element *e = __view_at(list, 0);

    return e->member->data;
}

void *view_last(dll *list) {
    element *e = __view_at(list, list->len - 1);

    return e->member->data;
}

void *view_at(dll *list, unsigned int index) {
    element *e = __view_at(list, index);

    if (e == NULL) {
        return NULL;
    } else {
        return e->member->data;
    }
}

element *__view_at(dll *list, unsigned int index) {
    // Check for least expensive way to traverse list
    unsigned int midpoint = list->len / 2;
    element *e;
    // Check if index is in range
    if (index >= list->len) {
        // Out of range
        return NULL;
    }

    if (index < midpoint) {
        // Traverse from head
        e = list->head;
        for (unsigned int i = 0; i != index; i++) {
            e = e->next;
        }
    } else {
        //Traverse from tail
        e = list->tail;
        for (unsigned int i = list->len - 1; i != index; i--) {
            e = e->prev;
        }
    }
    // e should now reference the wanted element
    return e;
}

dll *concat(dll *dest, dll *src) {
    dest->tail->next = src->head;
    src->head->prev = dest->tail;
    dest->tail = src->tail;
    dest->len += src->len;

    return dest;
}
