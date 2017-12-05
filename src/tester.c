#include "tester.h"

int main(int argc, char **argv) {
    build_and_destroy_flag();
    return 0;
}

void build_and_destroy_flag() {
    printf("Allocating flag\n");
    opt *flag = new_flag("test_flag", "c", "Help desc", "Man page desc");
    printf("Freeing flag\n");
    free_opt(flag);
    printf("Build-Destroy: Flag test passed\n");
}
