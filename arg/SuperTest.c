#include "SuperTest.h"
char* test_arg_parser(char* arg_str) {
    char* val = malloc(sizeof(char) * strlen(arg_str));
    strncpy(val, arg_str, strlen(arg_str));
    return val;
}

CUSTOM verbose_arg_parser(char* arg_str) {
    printf("No defined parser for type: CUSTOM\n");
}

