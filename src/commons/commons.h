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
#include <stdarg.h>

// Define program limits
#define MAX_STR_LEN 1024 * 20

// Define common function suffixes
#define HELP_SUFFIX "_help"
#define MAN_PAGE_SUFFIX "_man_page"

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

typedef struct {
    char *function_declaration;
    char *function_source;
} compiled_function;

// Define common functions
void free_pointer(void *occupied_memory);
char *copy_string(char *src);
char *combine_strings(char *prefix, char *suffix);

// Define primitive parser generators for C-Opts
char *compile_parse_integer(char *arg_str);
char *compile_parse_float(char *arg_str);
char *compile_parse_string(char *arg_str);
char *compile_parse_file(char *arg_str);
char *compile_parse_ipv4(char *arg_str);
char *compile_parse_ipv6(char *arg_str);
char *compile_parse_mac_addr(char *arg_str);

#endif
