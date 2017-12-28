#include "data.h"

/**
 * @brief This function creates a new container for data.
 * @param data The data to be encapsulated.
 * @param free_func A function specifying how the data should
 * be freed. Must take a void pointer as an input.
 */
container *new_container(void *data, void (*free_func) (void *)) {
    container *n_container = (container *) malloc(sizeof(container));
    n_container->data = data;
    n_container->free_func = free_func;
    n_container->references = 1;
    return n_container;
}

/**
 * @brief This function frees a container wrapping data.
 * @param cur_container The container to be freed. Its data
 * will be freed along with it.
 */
void free_container(container *cur_container) {
    cur_container->references--;
    if (cur_container->references == 0) {
        cur_container->free_func(cur_container->data);
        free(cur_container);
    }
}
