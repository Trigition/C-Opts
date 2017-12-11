#include "action.h"

/**
 * @brief This function frees any \ref action .
 * @param program_action A pointer to an \ref action.
 * This function completely frees an \ref action.
 * This includes not only each member of an \ref action
 * struct, but also each subaction. Any outside
 * references to memory belonging to the subtree will
 * need to be updated.
 */
void free_action(action *program_action) {
    free_pointer(program_action->action_name);
    free_pointer(program_action->action_desc);
    
    for (unsigned int i = 0; i < program_action->num_flags; i++) {
        free_opt(program_action->action_opts[i]);
    }

    free(program_action->action_opts);

    // Do a depth first free of the current tree branch
    for (unsigned int i = 0; i < program_action->num_subactions; i++) {
        free_action(program_action->subactions[i]);
    }

    free(program_action->subactions);

    // All reference dependencies have been freed, free the root.
    free(program_action);
}

action *new_action( char *action_name,
                    char *action_description,
                    opt **action_options,
                    unsigned int num_opts) {
    action *new_action = (action *) malloc(sizeof(action));
    if (new_action == NULL) {
        printf("Error in allocating memory for action: %s\n", action_name);
        return NULL;
    }

    new_action->action_opts = action_options;
    
    new_action->action_name = copy_string(action_name);
    new_action->action_desc = copy_string(action_description);

    new_action->subactions = NULL;
    new_action->num_flags = num_opts;
    new_action->num_subactions = 0;

    return new_action;
}

