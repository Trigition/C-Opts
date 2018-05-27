#include "primitive_parsers.h"

Function* PrimitiveParsers::default_parser(std::string &type, std::string &name) {
    Function *parser = new Function(name.c_str(), "void");
    std::string line = "printf(\"No defined parser for type: " + type + "\\n\")";
    parser->add_input_param(new Parameter("char*", "arg_str"));
    parser->add_codeline(line);
    return parser;
}

Function* PrimitiveParsers::get_int_parser(std::string &name) {
    // Create new function instance
    Function *parser = new Function(name.c_str(), "int");
    // Add required parameters to function
    parser->add_input_param(new Parameter("char*", "arg_str"));
    parser->add_codeline("int val = atoi(arg_str)");
    parser->add_codeline("return val");
    return parser;
}

Function* PrimitiveParsers::get_float_parser(std::string &name) {
    // Create new function instance
    Function *parser = new Function(name.c_str(), "float");
    // Add required paramters to function
    parser->add_input_param(new Parameter("char*", "arg_str"));
    parser->add_codeline("float val = atof(arg_str)");
    parser->add_codeline("return val");
    return parser;
}

Function* PrimitiveParsers::get_string_parser(std::string &name) {
    // Create new function instance
    Function *parser = new Function(name.c_str(), "char*");
    // Add required paramters to function
    parser->add_input_param(new Parameter("char*", "arg_str"));
    parser->add_codeline("char* val = malloc(sizeof(char) * strlen(arg_str))");
    parser->add_codeline("strncpy(val, arg_str, strlen(arg_str))");
    parser->add_codeline("return val");
    return parser;
}

Function* PrimitiveParsers::getParser(std::string &name, std::string &type) {
    if (type == "int") {
        return get_int_parser(name);
    } else if (type == "float") {
        return get_float_parser(name);
    } else if (type == "char*" || type == "char *") {
        return get_string_parser(name);
    } else {
        return default_parser(type, name);
    }
        // TODO Add more primitives
}

Function* PrimitiveParsers::getParser(c_str &name, c_str &type) {
    std::string str_name = name;
    std::string str_type = type;

    return getParser(str_name, str_type);
}
