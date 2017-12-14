#ifndef __OPT_H_
#define __OPT_H_

#include "commons/commons.h"

#define OPT_FUNCTION_SUFFIX "_parser"
#define OPT_FUNCTION_SUF_LEN strlen(OPT_FUNCTION_SUFFIX)

/*! \struct
 *  @brief This struct defines a commandline argument
 *  This struct encapsulates program arguments. This can range
 *  from positional arguments to positionless flags.
 */
typedef struct {
    char flag;
    char *long_flag;
    char *help_desc;
    char *man_desc;
    char *val;
    char *value_name;
    unsigned int opt_pos; // 1th pos considered to be positionless
    argtype opt_type;
    void * (*parser)(char *);
} opt;

// Begin Function Definitions

// Describe free functions for easy cleanup
void free_opt(opt *option);

// 'Constructor' functions for creating arguments
opt *allocate_opt();

opt *new_flag(  char *flag_name,
                char flag_char,
                char *help_description,
                char *man_page_description);

opt *new_argument(  char *arg_name,
                    char *value_name,
                    char *help_description,
                    char *man_page_description,
                    unsigned int position);

opt *valued_flag(   char *flag_name,
                    char flag_char,
                    char *value_name,
                    char *help_description,
                    char *man_page_description);

// Functions for augmenting currently existing objects
opt *assign_parser_function(opt *dest_opt, void * (*parser) (char *), argtype type);
opt *assign_cust_parser_function(opt *dest_opt, void * (*parser) (char *));

// Compilation functions
char *make_filename(opt *arg, const char *ext);
char *compile_parse_function(opt *arg);
char *compile_function_declaration(opt *arg);
compiled_function *compile_opt(opt *arg);
#endif
