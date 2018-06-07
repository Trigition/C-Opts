#include "primitiveParsers.h"

Function* PrimitiveParsers::defaultParser(std::string &type, std::string &name) {
    Function *parser = new Function(name.c_str(), "void");
    std::string line = "printf(\"No defined parser for type: " + type + "\\n\")";
    parser->addInputParam(new Parameter("char*", "arg_str"));
    parser->addCodeline(line);
    return parser;
}

Function* PrimitiveParsers::getIntParser(std::string &name) {
    // Create new function instance
    Function *parser = new Function(name.c_str(), "int");
    // Add required parameters to function
    parser->addInputParam(new Parameter("char*", "arg_str"));
    parser->addCodeline("int val = atoi(arg_str)");
    parser->addCodeline("return val");
    return parser;
}

Function* PrimitiveParsers::getFloatParser(std::string &name) {
    // Create new function instance
    Function *parser = new Function(name.c_str(), "float");
    // Add required paramters to function
    parser->addInputParam(new Parameter("char*", "arg_str"));
    parser->addCodeline("float val = atof(arg_str)");
    parser->addCodeline("return val");
    return parser;
}

Function* PrimitiveParsers::getStringParser(std::string &name) {
    // Create new function instance
    Function *parser = new Function(name.c_str(), "char*");
    // Add required paramters to function
    parser->addInputParam(new Parameter("char*", "arg_str"));
    parser->addCodeline("char* val = malloc(sizeof(char) * strlen(arg_str))");
    parser->addCodeline("strncpy(val, arg_str, strlen(arg_str))");
    parser->addCodeline("return val");
    return parser;
}

Function* PrimitiveParsers::getParser(std::string &name, std::string &type) {
    if (type == "int") {
        return getIntParser(name);
    } else if (type == "float") {
        return getFloatParser(name);
    } else if (type == "char*" || type == "char *") {
        return getStringParser(name);
    } else {
        return defaultParser(type, name);
    }
        // TODO Add more primitives
}

Function* PrimitiveParsers::getParser(c_str &name, c_str &type) {
    std::string stringName = name;
    std::string stringType = type;

    return getParser(stringName, stringType);
}
