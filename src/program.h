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
    char *program_desc;
    char *man_desc;
    char *program_version;
    dll *global_opts;
    dll *actions;
} program_opts;

void free_program_opt(program_opts *program);

program_opts *new_program(  char *program_description,
                            char *man_page_description,
                            char *program_version);

void assign_global_opt(program_opts *target_program, opt *global_opt);
void assign_action(program_opts *target_program, action *src_action);
void assign_actions(program_opts *target_program, dll *src_actions);
int compile_program(program_opts *target_program);
#endif
