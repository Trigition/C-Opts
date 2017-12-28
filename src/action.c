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

/**
 * @brief This function assigns opts to an action.
 * @TODO This should operate on a list of opts.
 * @TODO Remove double pointer passing
 */
void assign_opts(action *dest_action, opt **action_options, uint8 num_opts) {
    for (uint8 i = 0; i < num_opts; i++) {
        add_opt(dest_action, action_options[i]);
    }
}

/**
 * @brief This function assigns an opt to an action.
 * @param dest_action The action to assign an opt to.
 * @param option The option being assigned.
 */
void add_opt(action *dest_action, opt *option) {
    append_wfree(dest_action->action_opts, option, &free_opt);
}

/**
 * @brief This function assigns sub actions to an action.
 * @param dest_action The action to assign a subaction.
 * @param subaction The action being assigned as a subaction.
 * @TODO Program should check if a cyclic is being introduced and
 * prevent such behavior.
 */
void assign_subaction(action *dest_action, action *subaction) {
    append_wfree(dest_action->subactions, subaction, &free_action);
}

/**
 * @brief This function compiles function declarations of the action and
 * its subactions and opts.
 * @param target_action The action to compile.
 * @return A list of strings containing C code function declarations.
 */
dll *compile_header(action *target_action) {
    dll *opt_headers = new_list();
    
    //compiled_function *cur_function;
    for (unsigned int i = 0; i < target_action->action_opts->len; i++) {
        
    }
    return NULL;
}

/**
 * @brief This function compiles the action and its subactions and opts.
 * @param root_action The action to compile.
 * @return A list of compiled_functions representing all necessary C code
 * to parse the action and its possible subactions/arguments.
 */
dll *compile_action(action *root_action) {
    // Recursively compile the leaf nodes of the tree
    // with the current action as the root.
    if (root_action->subactions->len > 0) {
        action *cur_subaction;
        dll *compiled_functions;
        for (unsigned int i = 0; i < root_action->subactions->len; i++) {
            cur_subaction = view_at(root_action->subactions, i);
            compiled_functions = compile_action(cur_subaction);
            //@TODO Append functions to return
        }
    }
    // Compile action arguments
    if (root_action->action_opts->len > 0) {
        opt *cur_opt;
        dll *compiled_functions = new_list();
        for (unsigned int i = 0; i < root_action->action_opts->len; i++) {
            cur_opt = view_at(root_action->action_opts, i);
            append(compiled_functions, compile_opt(cur_opt));
            //@TODO Append functions to return
        }
    }
    return NULL;
}

/**
 * @brief This function compiles the parser function for an argument.
 */
dll *compile_action_parser(action *cur_action) {
    dll *function = new_list();
    char *function_name = combine_strings(cur_action->action_name, "_action_parser");
    append(function, copy_string("bool "));
    append(function, function_name);
    append(function, copy_string("(char *arg_string) {\n"));
    // Function code block
    append(function, copy_string("char *arg_name = \""));
    append(function, cur_action->action_name);
    append(function, copy_string("\";\n"));
    append(function, copy_string("return strcmp(arg_str, arg_string) == 0;\n"));
    // End function code block
    append(function, copy_string("\n}\n"));
    return function;
}
