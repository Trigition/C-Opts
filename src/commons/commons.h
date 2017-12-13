#ifndef __COMMONS_H_
#define __COMMONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define program limits
#define MAX_STR_LEN 1024 * 20

typedef enum {
   ARG_INT,
   ARG_FLOAT,
   ARG_STRING,
   ARG_FILE,
   ARG_IPV4,
   ARG_IPV6,
   ARG_MAC_ADDR,
   ARG_CUSTOM
} argtype;

// Define common functions
void free_pointer(void *occupied_memory);
char *copy_string(char *src);

#endif
