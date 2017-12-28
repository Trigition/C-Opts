#ifndef __DATA_H_
#define __DATA_H_

#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    void (*free_func) (void *);
    unsigned int references;
} container;

container *new_container(void *data, void (*free_func) (void *));
void free_container(container *cur_container);

#endif
