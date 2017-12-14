#ifndef __DATA_H_
#define __DATA_H_

#include <stdlib.h>

typedef struct {
    void *data;
    void (*free_func) (void *);
} container;

container *new_container(void *data, void (*free_func) (void *));
void free_container(container *cur_container);

#endif
