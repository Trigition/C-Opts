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
    struct opt **action_opts;
    struct action **subactions;
    unsigned int num_flags;
    unsigned int num_subactions;
} action;

void free_action(action *program_action);

action *new_action( char *action_name,
                    char *action_description,
                    struct opt **action_options,
                    unsigned int num_opts);
#endif
