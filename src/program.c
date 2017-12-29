#include "program.h"

/**
 * @brief This function frees any \ref program_opts.
 * @param program A pointer to a \ref program_opts.
 * This function completely frees a \ref program_opts.
 * This includes the entire argument tree and each node's
 * members. Any outside references to any memory
 * belonging to the tree will need to be updated.
 */
void free_program_opt(program_opts *program) {
    // Free all program actions
    delete_list(program->actions);

    free_pointer(program->program_desc);
    free_pointer(program->man_desc);
    free_pointer(program->program_version);

    free(program);
}

/**
 * @brief This function allocates a new program with specified data.
 * @param program_description A description of the program to be used
 * in help print-outs.
 * @param man_page_description A description that is used for man pages.
 * @param program_version The current version of the program.
 * @param program_actions An array of actions. //TODO If no actions are
 * present, the default action MAIN will be used.
 * @param num_actions The number of actions being passed. //TODO If no actions are
 * passed this value is igored.
 */
program_opts *new_program(  char *program_description,
                            char *man_page_description,
                            char *program_version) {
    program_opts *new_program = (program_opts *) malloc(sizeof(program_opts));
    
    // Check for any allocation error
    if (new_program == NULL) {
        printf("Error allocating program, please check computer memory usage\n");
        return NULL;
    }

    new_program->global_opts = new_list();
    new_program->actions = new_list();

    new_program->program_desc = copy_string(program_description);
    new_program->man_desc = copy_string(man_page_description);
    new_program->program_version = copy_string(program_version);
 
    return new_program;
}

/**
 * @brief This function assigns a new global argument.
 * @param target_program The program to have the new argument.
 * @param global_opt The argument.
 */
void assign_global_opt(program_opts *target_program, opt *global_opt) {
    // TODO Check to see if new opt is in conflict with any other
    // global or subaction opt.
    append_wfree(target_program->global_opts, global_opt, &free_opt);
}

void assign_action(program_opts *target_program, action *src_action) {
    // TODO Check to see if action is in conflict with any current
    // action
    append_wfree(target_program->actions, src_action, &free_action);
}

void assign_actions(program_opts *target_program, dll *src_actions) {
    if (target_program->actions != NULL) {
        delete_list(target_program->actions);
    }

    target_program->actions = src_actions;
}

/**
 * @brief This function compiles a program and writes all source
 * code to the appropriate file.
 * @return Returns 0 upon successful compilation
 * @TODO Error codes for erroneus input.
 */
int compile_program(program_opts *target_program) {
    return 1;
}
