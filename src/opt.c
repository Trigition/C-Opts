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
