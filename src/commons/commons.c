#include "commons.h"

/**
 * @brief This function frees any pointer.
 * @param occupied_memory A generic pointer.
 * This function frees any kind of pointer if it actually points
 * to a valid memory address.
 */
void free_pointer(void *occupied_memory) {
    if (occupied_memory != NULL) free(occupied_memory);
}
