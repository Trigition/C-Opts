#include "data.h"

container *new_container(void *data, void (*free_func) (void *)) {
    container *n_container = (container *) malloc(sizeof(container));
    n_container->data = data;
    n_container->free_func = free_func;
    return n_container;
}

void free_container(container *cur_container) {
    cur_container->free_func(cur_container->data);
    free(cur_container);
}
