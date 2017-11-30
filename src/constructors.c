#include "opt.h"

opt *allocate_opt() {
    opt *new_opt = (opt *) malloc(sizeof(opt));
    
    // Check for memory allocation success
    if (new_opt == NULL) {
        printf("Error in initializing option due to memory allocation error\n");
        return NULL;
    }

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

    new_opt->val = NULL;
    new_opt->value_name = NULL;
    new_opt->opt_pos = 0;

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

    new_opt->flag = NULL;
    new_opt->val = NULL;

    return new_opt;
}


