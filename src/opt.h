#ifndef __OPT_H_
#define __OPT_H_

#include "commons/commons.h"

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
    unsigned int opt_pos; // 0th pos considered to be positionless
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

#endif
