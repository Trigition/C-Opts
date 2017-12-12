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

char *copy_string(char *src) {
    size_t src_length = strlen(src) + 1;
    
    if (src_length > MAX_STR_LEN) {
        // Source string length is too long
        printf("Error, source string at %p exceeded max string length of %d\n", src, MAX_STR_LEN);
        return NULL;
    }

    // String length is valid
    char *new_string = (char *) malloc(sizeof(char) * src_length); 
    if (new_string == NULL) {
        // Error allocating block
        printf("Error allocating copy space for %s, string length %lu", src, src_length);
        return NULL;
    }
    return strncpy(new_string, src, src_length);
}
