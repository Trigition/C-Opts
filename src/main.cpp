#include "main.h"

#ifdef DEBUG_MODE
#pragma message "DEBUG MODE ON"
#endif

/**
 * @brief Main runtime for main
 */
int main(int argc, char **argv) {
    Program *test_prgm = new Program("Test", "Man Page Test", "0.0.1");
    Argument arg = Argument('t', "test", "help", "mp", "test_val", "str", 1);
    test_prgm->add_global_arg(arg);

    Compiler c = Compiler();

    test_prgm->accept(c);

    delete test_prgm;
    return 0;
}
