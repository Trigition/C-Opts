#ifndef __COMMONS_H_
#define __COMMONS_H_

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Define program limits
#define MAX_STR_LEN 1024 * 20

typedef unsigned char uchar;
typedef unsigned int uint8;

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

// Define primitive parsers for C-Opts
void *parse_integer(char *arg_str);
void *parse_float(char *arg_str);
void *parse_string(char *arg_str);
void *parse_file(char *arg_str);
void *parse_ipv4(char *arg_str);
void *parse_ipv6(char *arg_str);
void *parse_mac_addr(char *arg_str);

#endif
