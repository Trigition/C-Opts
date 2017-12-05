#include "tester.h"

int main(int argc, char **argv) {
    build_and_destroy_flag();
    build_and_destroy_arg();
    build_and_destroy_valued_flag();
    return 0;
}

void build_and_destroy_flag() {
    printf("Allocating flag\n");
    opt *flag = new_flag("test_flag", "c", "Help desc", "Man page desc");
    printf("Freeing flag\n");
    free_opt(flag);
    printf("Build-Destroy: Flag test passed\n");
}

void build_and_destroy_arg() {
    printf("Allocating arg\n");
    opt *arg = new_argument("test_arg", "arg-val", "Help desc", "Man page desc", 1);
    printf("Freeing arg\n");
    free_opt(arg);
    printf("Build-Destroy: Arg test passed\n");
}

void build_and_destroy_valued_flag() {
    printf("Allocating valued flag\n");
    opt *v_flag = valued_flag("valued_flag", "v", "flag-val", "Help desc", "Man page desc");
    printf("Freeing valued flag\n");
    free_opt(v_flag);
    printf("Build-Destroy: Valued Flag test passed\n");
}

void build_and_destroy_action() {

}

void build_and_destroy_program() {

}
