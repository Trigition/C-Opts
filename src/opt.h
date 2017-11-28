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
    unsigned int length;
} opt;

typedef struct {
    opt **mode_opts;
    struct mode **submodes;
    unsigned int num_children;
} mode;

typedef struct {
    
} program_opts;

// Begin Function Definitions

char *get_help_menu(program_opts *program);
char *write_program_opt_header(program_opts *program);

#endif
