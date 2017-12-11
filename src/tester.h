#ifndef __TESTER_H_
#define __TESTER_H_
#include <stdio.h>
#include <time.h>
#include "opt.h"

void logger(const char *tag, const char *message);

void build_and_destroy_flag();
void build_and_destroy_arg();
void build_and_destroy_valued_flag();
void build_and_destroy_action();
void build_and_destroy_program();

opt **make_lots_of_flags(unsigned int num);
opt **make_lots_of_args(unsigned int num);
opt **make_lots_of_valued_flags(unsigned int num);
action **make_lots_of_actions(unsigned int num);
program_opts **make_lots_of_programs(unsigned int num);

#endif
