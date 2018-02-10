#pragma once
#include "../commons/C_Code.h"

class PrimitiveParsers {
    public:
        static Function *get_int_parser(std::string &name);
        static Function *get_float_parser(std::string &name);
        static Function *get_string_parser(std::string &name);
        //static Function *get_file_parser(std::string &name);
        //static Function *get_ipv4_parser(std::string &name);
        //static Function *get_mac_addr_parser(std::string &name);
};
