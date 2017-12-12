#ifndef __PROGRAM_H_
#define __PROGRAM_H_

#include "opt.h"
#include "action.h"

/*! \struct
 *  @brief This struct defines a program
 *  This struct encapsulates programs. This struct is mainly for
 *  tree root operations for traversal and compilation of the tree
 *  into a C header file.
 */
typedef struct {
    unsigned int num_actions;
    char *program_desc;
    char *man_desc;
    char *program_version;
    struct action **actions;
} program_opts;

void free_program_opt(program_opts *program);

program_opts *new_program(  char *program_description,
                            char *man_page_description,
                            char *program_version,
                            struct action **program_actions,
                            unsigned int num_actions);
#endif
