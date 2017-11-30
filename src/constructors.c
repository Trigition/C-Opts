#include "opt.h"

opt *allocate_opt() {
    opt *new_opt = (opt *) malloc(sizeof(opt));
    
    // Check for memory allocation success
    if (new_opt == NULL) {
        printf("Error in initializing option due to memory allocation error\n");
        return NULL;
    }

    new_opt->flag = NULL;
    new_opt->long_flag = NULL;
    new_opt->help_desc = NULL;
    new_opt->man_desc = NULL;
    new_opt->val = NULL;
    new_opt->value_name = NULL;

    new_opt->opt_pos = 0; // Flags are set to positionless at default

    return new_opt;
}

opt *new_flag(  char *flag_name,
                char *flag_char,
                char *help_description,
                char *man_page_description) {

    opt *new_opt = allocate_opt();

    new_opt->long_flag = flag_name;
    new_opt->flag = flag_char;
    new_opt->help_desc = help_description;
    new_opt->man_desc = man_page_description;

    return new_opt;
}

opt *new_argument(  char *arg_name,
                    char *value_name,
                    char *help_description,
                    char *man_page_description,
                    unsigned int position) {

    opt *new_opt = allocate_opt();

    new_opt->long_flag = arg_name;
    new_opt->value_name = value_name;
    new_opt->help_desc = help_description;
    new_opt->man_desc = man_page_description;
    new_opt->opt_pos = position;

    return new_opt;
}

opt *valued_flag(   char *flag_name,
                    char *flag_char,
                    char *value_name,
                    char *help_description,
                    char *man_page_description) {
    opt *new_opt = allocate_opt();
    new_opt->long_flag = flag_name;
    new_opt->flag = flag_name;
    new_opt->value_name = value_name;
    new_opt->help_desc = help_description;
    new_opt->man_desc = man_page_description;

    return new_opt;
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
    new_action->action_name = action_name;
    new_action->action_desc = action_description;
    new_action->action_opts = action_options;
    new_action->subactions = NULL;
    new_action->num_flags = num_opts;
    new_action->num_subactions = 0;

    return new_action;
}

program_opts *new_program(  char *program_description,
                            char *man_page_description,
                            char *program_version,
                            action **program_actions,
                            unsigned int num_actions) {
    program_opts *new_program = (program_opts *) malloc(sizeof(new_program));
    
    // Check for any allocation error
    if (new_program == NULL) {
        printf("Error allocating program, please check computer memory usage\n");
        return NULL;
    }

    new_program->program_desc = program_description;
    new_program->man_desc = man_page_description;
    new_program->program_version = program_version;
    new_program->actions = program_actions; //TODO Default to 'main' action if none
    new_program->num_actions = num_actions;

    return new_program;
}
