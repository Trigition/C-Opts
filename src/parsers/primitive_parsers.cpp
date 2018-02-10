#include "primitive_parsers.h"

Function* PrimitiveParsers::get_int_parser(std::string &name) {
    // Create new function instance
    Function *parser = new Function(name.c_str(), "int");
    // Add required parameters to function
    parser->add_input_param(new Parameter("char *", "arg_str"));
    parser->add_codeline("int val = atoi(arg_str)");
    parser->add_codeline("return val");
    return parser;
}

Function* PrimitiveParsers::get_float_parser(std::string &name) {
    // Create new function instance
    Function *parser = new Function(name.c_str(), "float");
    // Add required paramters to function
    parser->add_input_param(new Parameter("char *", "arg_str"));
    parser->add_codeline("float val = atof(arg_str)");
    parser->add_codeline("return val");
    return parser;
}

Function* PrimitiveParsers::get_string_parser(std::string &name) {
    // Create new function instance
    Function *parser = new Function(name.c_str(), "char *");
    // Add required paramters to function
    parser->add_input_param(new Parameter("char *", "arg_str"));
    parser->add_codeline("char *val = malloc(sizeof(char) * strlen(arg_str))");
    parser->add_codeline("strncpy(val, arg_str, strlen(arg_str))");
    parser->add_codeline("return val");
    return parser;
}
