#include "tester.h"

/**
 * @brief Main runtime for main
 */
int main(int argc, char **argv) {
    build_and_destroy_list();

    build_and_destroy_flag();
    build_and_destroy_arg();
    build_and_destroy_valued_flag();
    build_and_destroy_action();
    build_and_destroy_program();

    build_and_compile_flag();
    return 0;
}

void logger(const char *tag, const char *message) {
    //time_t now;
    //time(&now);
    //printf("%s [%s]: %s\n", ctime(&now), tag, message);
    printf("[%s]: %s\n", tag, message);
}

void build_and_destroy_list() {
    int x = 1;
    int y = 2;
    int z = 3;
    logger(__FUNCTION__, "Allocating list");
    dll *list = new_list();
    logger(__FUNCTION__, "Adding to list");
    push(list, &x);
    if (list->len == 1) {
        logger(__FUNCTION__, "List length correct");
    } else {
        logger(__FUNCTION__, "ERROR list length incorrect");
    }

    if (*(int *) view_first(list) == x) {
        logger(__FUNCTION__, "List contents correct");
    } else {
        logger(__FUNCTION__, "ERROR list length incorrect");
    }

    logger(__FUNCTION__, "Appending to list");
    append(list, &y);
    if (list->len == 2) {
        logger(__FUNCTION__, "List length correct");
    } else {
        logger(__FUNCTION__, "List length incorrect");
    }

    if (*(int *) view_last(list) == y) {
        logger(__FUNCTION__, "List contents correct");
    } else {
        logger(__FUNCTION__, "List contents incorrect");
    }

    soft_delete_list(list);
}

void build_and_destroy_flag() {
    logger(__FUNCTION__, "Allocating Flag");
    opt *flag = new_flag("test_flag", 'c', "Help desc", "Man page desc");
    logger(__FUNCTION__, "Freeing Flag");
    free_opt(flag);
    logger(__FUNCTION__, "Flag test passed");
}

void build_and_destroy_arg() {
    logger(__FUNCTION__, "Allocating Arg");
    opt *arg = new_argument("test_arg", "arg-val", "Help desc", "Man page desc", 1);
    logger(__FUNCTION__, "Freeing arg");
    free_opt(arg);
    logger(__FUNCTION__, "Arg test passed");
}

void build_and_destroy_valued_flag() {
    logger(__FUNCTION__, "Allocating Arg");
    opt *v_flag = valued_flag("valued_flag", 'v', "flag-val", "Help desc", "Man page desc");
    logger(__FUNCTION__, "Freeing Valued Flag");
    free_opt(v_flag);
    logger(__FUNCTION__, "Valued Flag test passed");
}

void build_and_destroy_action() {
    logger(__FUNCTION__, "Allocating Args");
    opt **flags = make_lots_of_flags(200);
    logger(__FUNCTION__, "Allocating Action");
    action *act = new_action("Action!", "Help desc", flags, 200);
    logger(__FUNCTION__, "Freeing Action");
    free_action(act);
    logger(__FUNCTION__, "Action test passed");
}

void build_and_destroy_program() {
    logger(__FUNCTION__, "Allocating Actions");
    action **actions = make_lots_of_actions(10);
    logger(__FUNCTION__, "Allocating program");
    program_opts *program = new_program("A Generated test program",
                                        "Test program man page",
                                        "0.0.1", 
                                        actions,
                                        10);
    logger(__FUNCTION__, "Freeing program");
    free_program_opt(program);
    logger(__FUNCTION__, "Program test passed");
}

void build_and_compile_flag() {
    logger(__FUNCTION__, "Allocating Flag");
    opt *flag = new_flag("TESTFLAG", 'f', "Test Flag Description", "Manly Page");
    logger(__FUNCTION__, "Compiling Flag...");
    compiled_function *flag_functions = compile_opt(flag);
    logger(__FUNCTION__, "Compiled flag, freeing memory");
    free_opt(flag);
    free_compiled_function(flag_functions);
    logger(__FUNCTION__, "Passed");
}

opt **make_lots_of_flags(unsigned int num) {
    char flag_name[100];
    char flag_char;
    opt **flags = malloc(sizeof(opt *) * num);
    for (unsigned int i = 0; i < num; i++) {
        flag_char = i % 256;
        snprintf(flag_name, 100, "Flag %u", i);
        flags[i] = new_flag(flag_name, flag_char, "Help Desc", "Man Page Desc");
    }
    return flags;
}

action **make_lots_of_actions(unsigned int num) {
    char action_name[100];
    action **actions = malloc(sizeof(action *) * num);
    for (unsigned int i = 0; i < num; i++) {
        snprintf(action_name, 100, "Action %u", i);
        actions[i] = new_action(action_name, "Help Desc", make_lots_of_flags(200), 200);
    }
    return actions;
}
