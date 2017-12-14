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

/**
 * @brief This function allocates an opt.
 * This function allocates memory for an opt struct.
 * Members of this struct are initialized to 0 or NULL
 * depending on their representative types.
 * @return This function returns a pointer to the allocated
 * opt. It must be freed manually.
 */
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

    // All opts by default parse for strings
    new_opt->parser = &compile_parse_string;
    new_opt->opt_type = ARG_STRING;

    return new_opt;
}

/**
 * @brief This allocates an opt struct as a flag.
 * @param flag_name This is the name for the flag. The longhand flag will
 * use this name e.g --FLAG_NAME. As so it cannot contain '-'. 
 * Referencing this flag will require use of its name e.g. 
 * args->action->FLAG_NAME. The name must be unique in the scope of 
 * its action and super actions.
 * @param flag_char This is the shorthand specifier for the flag. It is
 * used for only creating shorthand specifiers e.g. '-v' for --verbose.
 * Like flag_name, this character must be unique in the scope of its
 * action and super actions.
 *
 * This functions allocates memory for an opt struct and specifies data
 * for the opt to represent a flag.
 * @return Returns the allocated opt.
 */
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

/**
 *  @brief This function allocates an opt struct to be a positional argument.
 *  @param arg_name This is the name for the argument. Referencing the value
 *  for the argument will require the use of its name: e.g args->action->arg_name.
 *  The name must be unique in the scope of its action.
 *  @param value_name This name for the value is used for help and man page print outs.
 *  @param help_description The help print-out description for this argument.
 *  @param man_page_description The man page description for this argument.
 *  @param position The position, relative to the position of its parent action, the argument
 *  should reside in. Conflicting/missing positions will throw an error upon
 *  argument parser compilation.
 *  @return Returns the allocated opt.
 */
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

/**
 * @brief This function allocates a positionless valued argument.
 * @param flag_name This is the name for the flag. The longhand flag will
 * use this name e.g --FLAG_NAME. As so it cannot contain '-'. 
 * Referencing this flag will require use of its name e.g. 
 * args->action->FLAG_NAME. The name must be unique in the scope of 
 * its action and super actions.
 * @param flag_char This is the shorthand specifier for the flag. It is
 * used for only creating shorthand specifiers e.g. '-v' for --verbose.
 * Like flag_name, this character must be unique in the scope of its
 * action and super actions.
 * @param value_name This name for the value is used for help and man page print outs.
 * @param help_description The help print-out description for this argument.
 * @param man_page_description The man page description for this argument.
 * @return Returns the allocated opt.
 */
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

/**
 * @brief This function assigns a parser to an opt struct for typechecking and loading.
 * @param dest_opt The opt to assign a function to.
 * @param parser The parsing function. It must return a void pointer / NULL upon failure.
 * @param type The type of data that is returned upon a successful parse.
 * @return Returns the modified opt.
 */
opt *assign_parser_function(opt *dest_opt, char * (*parser) (), argtype type) {
    dest_opt->parser = parser;
    dest_opt->opt_type = type;

    return dest_opt;
}

/**
 * @brief A shorthand function to assigning a custom parser. The argtype of the opt
 * is automatically ARG_CUSTOM.
 * @param dest_opt The opt to assign a function to.
 * @param parser The parsing function. It must returna void pointer / NULL upon failure.
 * @return Returns the modified opt.
 */
opt *assign_cust_parser_function(opt *dest_opt, char * (*parser) ()) {
    dest_opt->parser = parser;
    dest_opt->opt_type = ARG_CUSTOM;

    return dest_opt;
}

char *make_filename(opt *arg, const char *ext) {
    char *opt_name = arg->long_flag;
    char *filename = (char *) malloc(strlen(opt_name) * sizeof(char) + 
                                     strlen(ext) * sizeof(char));
    filename = copy_string(opt_name);
    filename = strcat(filename, ext);
    return filename;
}

char *compile_parse_function(opt *arg) {
    // Do boiler plate setup
    char *function_name = combine_strings(arg->long_flag, OPT_FUNCTION_SUFFIX);
    char *source = arg->parser();
    uint8 function_len = strlen(function_name) + strlen(source) + 50;
    char *function = malloc(function_len * sizeof(char));

    strcat(function, function_name);
    strcat(function, "(char *arg_str) {\n");
    strcat(function, source);
    strcat(function, "\n}\n");

    free(function_name);
    free(source);
    return function;
}

char *compile_function_declaration(opt *arg) {
    // Do boiler plate setup
    char *function_name = combine_strings(arg->long_flag, OPT_FUNCTION_SUFFIX);
    char *function_suffix = "(char *arg_str);\n";
    char *function_declaration = combine_strings(function_name, function_suffix);
    free(function_name);
    return function_declaration;
}

compiled_function *compile_opt(opt *arg) {
    compiled_function *compiled_opt = (compiled_function *) malloc(sizeof(compiled_function));
    compiled_opt->function_declaration = compile_function_declaration(arg);
    compiled_opt->function_source = compile_parse_function(arg);
    return compiled_opt;
}
