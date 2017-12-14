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

void free_compiled_function(compiled_function *func) {
    free(func->function_declaration);
    free(func->function_source);
    free(func);
}

/**
 * A function to help in the copy of a string. Using strncpy
 * it avoids buffer overflows. A max length of MAX_STR_LEN (see commons)
 * any string longer than this value will not be copied.
 * @param src A pointer to the source string
 * @return Returns a pointer to the copy. NULL if an error occured.
 */
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

char *combine_strings(char *prefix, char *suffix) {
    uint8 total_size = strlen(prefix) + strlen(suffix) + 1;
    if (total_size > MAX_STR_LEN) {
        printf("Error, combined string length beyond maximum allowed length: %d\n",
                MAX_STR_LEN);
        return NULL;
    }
    char *buf = malloc(total_size * sizeof(char));
    buf[0] = '\0';
    buf = strcat(buf, prefix);
    buf = strcat(buf, suffix);
    return buf;
}

char *compile_parse_integer() {
    char *func = \
    "// Use standard libraries to parse integers\
    long long *val = malloc(sizeof(long long));\
    errno = 0;\
    *val = strtol(arg_str, NULL, 10);\
    if (errno != 0) {\
        // Error in parsing string for integer\
        free(val);\
        return NULL;\
    }\
    return val;";
    return copy_string(func);
}

char *compile_parse_float() {
    char *func = \
    "float *val = malloc(sizeof(float));\
    \
    errno = 0;\
    *val = strtof(arg_str, NULL);\
    if (errno != 0) {\
        // Error in parsing float\
        free(val);\
        return NULL;\
    } else {\
        return val;\
    }";
    return copy_string(func);
}

char *compile_parse_string() {
    char *func = \
    "char *str_copy = copy_string(arg_str);\
    return str_copy;";
    return copy_string(func);
}

char *compile_parse_file() {
    char *func = \
    "if (access( arg_str, F_OK) != -1) {\
        return arg_str;\
    } else {\
        return NULL;\
    }";
    return func;
}

char *compile_parse_ipv4() {
    // TODO Tokenize ipv4 string
    return NULL;
}
