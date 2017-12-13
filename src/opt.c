#include "opt.h"

// Cleanup functions
/**
 * @brief This function frees any \ref opt .
 * @param option A pointer to an \ref opt
 * This function completely frees an \ref Any member
 * of the struct is also freed with it. Any outside reference
 * must be manually updated to reflect the free.
 */
void free_opt(opt *option) {
    free_pointer(option->long_flag);
    free_pointer(option->help_desc);
    free_pointer(option->man_desc);
    free_pointer(option->val);
    free_pointer(option->value_name);

    free(option);
}

opt *allocate_opt() {
    opt *new_opt = (opt *) malloc(sizeof(opt));
    
    // Check for memory allocation success
    if (new_opt == NULL) {
        printf("Error in initializing option due to memory allocation error\n");
        return NULL;
    }

    new_opt->flag = 0;
    new_opt->long_flag = NULL;
    new_opt->help_desc = NULL;
    new_opt->man_desc = NULL;
    new_opt->val = NULL;
    new_opt->value_name = NULL;

    new_opt->opt_pos = 0; // Flags are set to positionless at default

    return new_opt;
}

opt *new_flag(  char *flag_name,
                char flag_char,
                char *help_description,
                char *man_page_description) {

    opt *new_opt = allocate_opt();

    new_opt->long_flag = copy_string(flag_name);
    new_opt->flag = flag_char;
    new_opt->help_desc = copy_string(help_description);
    new_opt->man_desc = copy_string(man_page_description);

    return new_opt;
}

opt *new_argument(  char *arg_name,
                    char *value_name,
                    char *help_description,
                    char *man_page_description,
                    unsigned int position) {

    opt *new_opt = allocate_opt();

    new_opt->long_flag = copy_string(arg_name);
    new_opt->value_name = copy_string(value_name);
    new_opt->help_desc = copy_string(help_description);
    new_opt->man_desc = copy_string(man_page_description);

    new_opt->opt_pos = position;

    return new_opt;
}

opt *valued_flag(   char *flag_name,
                    char flag_char,
                    char *value_name,
                    char *help_description,
                    char *man_page_description) {
    opt *new_opt = allocate_opt();

    new_opt->long_flag = copy_string(flag_name);
    new_opt->flag = flag_char;
    new_opt->value_name = copy_string(value_name);
    new_opt->help_desc = copy_string(help_description);
    new_opt->man_desc = copy_string(man_page_description);

    return new_opt;
}

opt *assign_parser_function(opt *dest_opt, void * (*parser) (char *), argtype type) {
    dest_opt->parser = parser;
    dest_opt->opt_type = type;

    return dest_opt;
}

opt *assign_cust_parser_function(opt *dest_opt, void * (*parser) (char *)) {
    dest_opt->parser = parser;
    dest_opt->opt_type = ARG_CUSTOM;

    return dest_opt;
}
