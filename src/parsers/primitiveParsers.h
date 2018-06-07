#pragma once
#include "../commons/Function.h"
#include "../commons/Parameter.h"

class PrimitiveParsers {
    public:
        static Function *defaultParser(std::string &type, std::string &name);
        static Function *getIntParser(std::string &name);
        static Function *getFloatParser(std::string &name);
        static Function *getStringParser(std::string &name);
        //static Function *get_fileParser(std::string &name);
        //static Function *get_ipv4Parser(std::string &name);
        //static Function *get_mac_addrParser(std::string &name);
        static Function *getParser(std::string &name, std::string &type);
        static Function *getParser(c_str &name, c_str &type);
};
