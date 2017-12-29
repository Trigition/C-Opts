#ifndef __C_CODE_H_
#define __C_CODE_H_

#include "commons.h"

// Define formatting options
typedef enum {
    KR,
    Allman,
    GNU,
    Whitesmiths,
    Horstmann,
    Pico,
    Ratliff,
    Lisp
} indent_style;

typedef struct {
    indent_style style;
    uchar spaces_per_indent;
} formatting;

typedef struct {
    dll *code_lines;
    uint8 depth; // For formatting purposes
} code_block;

typedef struct {
    char *function_name;
    char *return_type;
    dll *function_args;
    code_block *code;
} c_function;

c_function *new_function(const char *name, const char *return_type);
void add_param(c_function *function, const char *type, const char *name);

void free_c_function(c_function *f);
void free_code_block(code_block *b);
#endif
