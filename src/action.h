#ifndef __ACTION_H_
#define __ACTION_H_

#include "datastructures/dll.h"
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
    dll  *action_opts;
    dll  *subactions;
} action;

void free_action(void *target_action);

action *new_action( char *action_name,
                    char *action_description);

void assign_opts(action *dest_action, opt **action_options, uint8 num_opts);
void assign_subactions(action *dest_action, action **subactions, uint8 num_actions);
void add_opt(action *dest_action, opt *option);
char *compile_header(action *cur_action);
compiled_function *compile_action(action *cur_action);
#endif
