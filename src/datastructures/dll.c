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
 * @brief This function creates a list from an array of ints
 * @param array This is the array of ints
 * @param len The length of the array to copy
 */
dll *list_from_ints(int *array, unsigned int len) {
    dll *list = new_list();

    for (unsigned int i = 0; i < len; i++) {
        append(list, &array[i]);
    }

    return list;
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
        free(prev_element->member);
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
    if (old_head != NULL) {
        old_head->prev = new_head;
        new_head->next = old_head;
    } else {
        // List was empty
        list->tail = new_head;
    }
    list->head = new_head;
    list->len++;
}

/**
 * @brief This function places data at the end of a list
 * @param list The destination list.
 * @param data The data to be added.
 */
void append(dll *list, void *data) {
    element *new_tail = new_element(data);

    __append(list, new_tail);
}

/**
 * @brief This function places data at the end of a list with
 * a custom free function.
 * @param list The destination list.
 * @param data The data to be added.
 * @param free_func The free function. It must take a void pointer an input.
 */
void append_wfree(dll *list, void *data, void (*free_func) (void *)) {
    element *new_tail = new_element_wfree(data, free_func);

    __append(list, new_tail);
}

/**
 * @brief An internal function to place dll elements on a list.
 * @param list The destination list.
 * @param new_tail The dll element to be placed at the end of the list.
 */
void __append(dll *list, element *new_tail) {
    element *old_tail = list->tail;
    if(old_tail != NULL) {
        old_tail->next = new_tail;
        new_tail->prev = old_tail;
    } else {
        list->head = new_tail;
    }
    list->tail = new_tail;
    list->len++;
}

/**
 * @brief This function inserts data somewhere within the list.
 * @param list The destination list.
 * @param data The data to be placed.
 * @param index Where the data should be placed.
 */
void insert(dll *list, void *data, unsigned int index) {
    element *e = new_element(data);

    __insert(list, e, index);
}

/**
 * @brief This function inserts data somewhere within a list with a custom free function.
 * @param list The destination list.
 * @param data The data to be placed.
 * @param index Where the data should be placed.
 * @param free_func A function to free the data. Must take a void pointer as input.
 *
 */
void insert_wfree(dll *list, void *data, unsigned int index, void (*free_func) (void *)) {
    element *e = new_element_wfree(data, free_func);

    __insert(list, e, index);
}

/**
 * @brief An internal function to place dll elements somewhere within a list.
 * @param e The element to be inserted.
 * @param index Where the element should be inserted at.
 */
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

/**
 * @brief This internal function removes element at a specific index.
 * @param list The source list.
 * @param index The nth element to remove.
 * @return The removed element.
 */
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

/**
 * @brief This function views the first element of a list.
 * @param list The source list
 * @return A void pointer to the data at the front of a list.
 */
void *view_first(dll *list) {
    element *e = __view_at(list, 0);

    return e->member->data;
}

/**
 * @brief This function views the last element of a list.
 * @param list The source list.
 * @return A void pointer to the data at the back of a list.
 */
void *view_last(dll *list) {
    element *e = __view_at(list, list->len - 1);

    return e->member->data;
}

/**
 * @brief This function views the data at a specific index.
 * @param list The source list.
 * @param index The position of the desired data.
 * @return A void pointer to the data at the index. NULL if no
 * such position exists.
 */
void *view_at(dll *list, unsigned int index) {
    element *e = __view_at(list, index);

    if (e == NULL) {
        return NULL;
    } else {
        return e->member->data;
    }
}

/**
 * @brief An internal function to view elements at an index.
 * @param list The source list.
 * @param index The position of the desired element.
 * @return An element pointer for use in view_first, view_last,
 * and view_at.
 */
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

/**
 * @brief This function appends one list to
 * another.
 * @param dest The destination list. This list
 * will be altered to contain the source list.
 * @param src The list to be appended. This list
 * will remain untouched.
 * @return A pointer to the destination.
 */
//TODO Update number of references for source
dll *concat(dll *dest, dll *src) {
    dest->tail->next = src->head;
    src->head->prev = dest->tail;
    dest->tail = src->tail;
    dest->len += src->len;

    return dest;
}

/**
 * @brief This function will copy a list's elements into
 * a new list. This is a shallow copy.
 * @param src The list to be copied.
 * @return A reference to the new list. It's data will be pointers
 * to the source's data. Any changes in the source or destination will be
 * refleced in both.
 */
dll *copy_lists(dll *src) {
    dll *copy = new_list();
    element *cur_element = src->head;
    for (unsigned int i = 0; i < src->len; i++) {
        append_wfree(copy, cur_element->member->data, cur_element->member->free_func);
        cur_element->member->references++;
        cur_element = cur_element->next;
    }
    return copy;
}

/**
 * @brief This function deeply copies a list, meaning all data
 * is duplicated in memory.
 * @param src The list to be copied
 * @return A reference to the new list. All data has been duplicated.
 * Any changes in the source or copy will not be reflected in the other.
 */
dll *deep_copy(dll *src) {
    dll *copy = new_list();
    element *cur_element = src->head;
    void *data = NULL;

    for (unsigned int i = 0; i < src->len; i++) {
        size_t data_size = sizeof(*cur_element->member->data);
        data = malloc(sizeof(data_size));
        memcpy(data, cur_element->member->data, data_size);
        append_wfree(copy, data, cur_element->member->free_func);
        cur_element = cur_element->next;
    }

    return copy;
}
