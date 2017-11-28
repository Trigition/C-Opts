#ifndef __OPT_H_
#define __OPT_H_

/*! \struct
 *  \brief This struct defines a commandline argument
 */
typedef struct {
    char *flag;
    char *long_flag;
    char *help_desc;
    char *man_desc;
    char *val;
    unsigned int opt_pos; // 0th pos considered to be positionless
} opt;

typedef struct {
    char *action_name;
    char *action_desc;
    opt **action_opts;
    struct action **subactions;
    unsigned int num_children;
} action;

typedef struct {
    char *program_desc;
    char *man_desc;
    char *program_version;
    action **actions;
} program_opts;

// Begin Function Definitions

// Describe free functions for easy cleanup
void free_opt(opt *option);
void free_action(action *action);
void free_program_opt(program_opts *program);
void free_program_tree(program_opts *program);

// 'Constructor' functions for creating arguments
opt *new_flag(  char *flag_name,
                char *flag_char,
                char *help_description,
                char *man_page_description);

opt *new_argument(  char *arg_name,
                    char *help_description,
                    char *man_page_description,
                    unsigned int position);

opt *new_action(char *action_name,
                char *action_description,
                opt **action_options);

program_opts *new_program(  char *program_description,
                            char *man_page_description,
                            char *program_version,
                            action **program_actions);

// Functions for augmenting currently existing objects

// Functions for header/C code write outs
char *get_help_menu(program_opts *program);
char *write_program_opt_header(program_opts *program);

#endif
