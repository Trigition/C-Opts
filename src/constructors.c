#include "opt.h"
#include "action.h"
#include "program.h"

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

char *copy_string(char *src) {
    size_t src_length = strlen(src);
    
    if (src_length > MAX_STR_LEN) {
        // Source string length is too long
        printf("Error, source string at %p exceeded max string length of %d\n", src, MAX_STR_LEN);
        return NULL;
    }

    // String length is valid
    char *new_string = (char *) malloc(sizeof(char) * src_length + 1); // Allow another byte for null terminator
    strncpy(new_string, src, src_length);
    return new_string;
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
