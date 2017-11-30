#include "opt.h"

char *get_help_menu(program_opts *program) {
    return "IMPLEMENT";
}

char *write_program_opt_header(program_opts *program) {
    return "IMPLEMENT";
}

// Cleanup functions

/**
 * @brief This function frees any pointer.
 * @param occupied_memory A generic pointer.
 * This function frees any kind of pointer if it actually points
 * to a valid memory address.
 */
void free_pointer(void *occupied_memory) {
    if (occupied_memory != NULL) free(occupied_memory);
}

/**
 * @brief This function frees any \ref opt .
 * @param option A pointer to an \ref opt
 * This function completely frees an \ref Any member
 * of the struct is also freed with it. Any outside reference
 * must be manually updated to reflect the free.
 */
void free_opt(opt *option) {
    free_pointer(option->flag);
    free_pointer(option->long_flag);
    free_pointer(option->help_desc);
    free_pointer(option->man_desc);
    free_pointer(option->val);
    free_pointer(option->value_name);

    free(option);
}

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

    // Do a depth first free of the current tree branch
    for (unsigned int i = 0; i < program_action->num_subactions; i++) {
        free_action(program_action->subactions[i]);
    }

    // All reference dependencies have been freed, free the root.
    free(program_action);
}

/**
 * @brief This function frees any \ref program_opts.
 * @param program A pointer to a \ref program_opts.
 * This function completely frees a \ref program_opts.
 * This includes the entire argument tree and each node's
 * members. Any outside references to any memory
 * belonging to the tree will need to be updated.
 */
void free_program_opt(program_opts *program) {
    free_pointer(program->program_desc);
    free_pointer(program->man_desc);
    free_pointer(program->program_version);

    // Free all program actions
    for (unsigned int i = 0; i < program->num_actions; i++) {
        free_action(program->actions[i]);
    }

    free(program);
}
