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

void *parse_integer(char *arg_str) {
    // Use standard libraries to parse integers
    long long *val = malloc(sizeof(long long));
    //const char *errstr;

    //*val = strtonum(arg_str, LLONG_MIN, LLONG_MAX, &errstr);
    //if (errstr != NULL) {
    //    free(val);
    //    return NULL;
    //} else {
    //    return val;
    //}

    // Setup error checking
    errno = 0;
    *val = strtol(arg_str, NULL, 10);
    if (errno != 0) {
        // Error in parsing string for integer
        free(val);
        return NULL;
    }
    return val;
}

void *parse_float(char *arg_str) {
    float *val = malloc(sizeof(float));
    
    errno = 0;
    *val = strtof(arg_str, NULL);
    if (errno != 0) {
        // Error in parsing float
        free(val);
        return NULL;
    } else {
        return val;
    }
}

void *parse_string(char *arg_str) {
    char *str_copy = copy_string(arg_str);
    return str_copy;
}

void *parse_file(char *arg_str) {
    if (access( arg_str, F_OK) != -1) {
        return arg_str;
    } else {
        return NULL;
    }
}

void *parse_ipv4(char *arg_str) {
    // TODO Tokenize ipv4 string
    return NULL;
}
