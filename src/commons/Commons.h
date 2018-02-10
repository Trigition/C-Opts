#pragma once

#include <iostream>
#include <vector>
#include <string>

// Define program limits
#define MAX_STR_LEN 1024 * 20

// Define common function suffixes
#define HELP_SUFFIX "_help"
#define MAN_PAGE_SUFFIX "_man_page"

#define NO_VAL "__NO__VALUE__"

#define DEBUG_MODE

typedef unsigned char uchar;
typedef unsigned int uint8;
typedef const char * const c_str;

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
