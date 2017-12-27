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
void free_action(void *target_action) {
    action *program_action = (action *) target_action;
    free_pointer(program_action->action_name);
    free_pointer(program_action->action_desc);
    
    delete_list(program_action->action_opts);
    delete_list(program_action->subactions);

    // All reference dependencies have been freed, free the root.
    free(program_action);
}

/**
 * @brief This function allocates a new action with specified data.
 * @param action_name This name is used for help print outs as well
 * as referencing e.g args->ACTION_NAME->foo. The name must be unique
 * to its sibling and parent actions.
 * @param action_description The help print-out description for the action.
 * @param action_opts An array of opts to be assigned to the action.
 * @param num_opts The number of opts in the passed array.
 * @return Returns the allocated action or NULL upon failed allocation.
 */
action *new_action( char *action_name,
                    char *action_description) {
    
    action *new_action = (action *) malloc(sizeof(action));
    
    if (new_action == NULL) {
        printf("Error in allocating memory for action: %s\n", action_name);
        return NULL;
    }

    new_action->action_opts = new_list();
    new_action->subactions = new_list();

    new_action->action_name = copy_string(action_name);
    new_action->action_desc = copy_string(action_description);

    return new_action;
}

void assign_opts(action *dest_action, opt **action_options, uint8 num_opts) {
    for (uint8 i = 0; i < num_opts; i++) {
        add_opt(dest_action, action_options[i]);
    }
}

void add_opt(action *dest_action, opt *option) {
    append_wfree(dest_action->action_opts, option, &free_opt);
}

void assign_subaction(action *dest_action, action *subaction) {
    append_wfree(dest_action->subactions, subaction, &free_action);
}

char *compile_header(action *cur_action) {
    dll *opt_headers = new_list();
    
    compiled_function *cur_function;
    for (unsigned int i = 0; i < cur_action->action_opts->len; i++) {
        
    }
    return NULL;
}

compiled_function *compile_action(action *root_action) {
    return NULL;
}
