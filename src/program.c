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
    for (unsigned int i = 0; i < program->num_actions; i++) {

        free_action(program->actions[i]);
    }
    free(program->actions);

    free_pointer(program->program_desc);
    free_pointer(program->man_desc);
    free_pointer(program->program_version);

    free(program);
}

program_opts *new_program(  char *program_description,
                            char *man_page_description,
                            char *program_version,
                            action **program_actions,
                            unsigned int num_actions) {
    program_opts *new_program = (program_opts *) malloc(sizeof(program_opts));
    
    // Check for any allocation error
    if (new_program == NULL) {
        printf("Error allocating program, please check computer memory usage\n");
        return NULL;
    }

    new_program->actions = program_actions; //TODO Default to 'main' action if none
    new_program->num_actions = num_actions;

    new_program->program_desc = copy_string(program_description);
    new_program->man_desc = copy_string(man_page_description);
    new_program->program_version = copy_string(program_version);
 
    return new_program;
}
