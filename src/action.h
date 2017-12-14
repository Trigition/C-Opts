#ifndef __ACTION_H_
#define __ACTION_H_

#include "commons/commons.h"
#include "opt.h"

/*! \struct
 *  @brief This struct defines a program action
 *  This struct encapsulates program actions. Actions 
 *  dictate different operations a program can perform.
 *  Options are specific to a certain action and its subactions.
 */
typedef struct action {
    char *action_name;
    char *action_desc;
    opt **action_opts;
    struct action **subactions;
    unsigned int num_flags;
    unsigned int num_subactions;
} action;

void free_action(action *program_action);

action *new_action( char *action_name,
                    char *action_description,
                    opt **action_options,
                    unsigned int num_opts);

char *compile_header(action *cur_action);
compiled_function *compile_action(action *cur_action);
#endif
