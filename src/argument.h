#pragma once

#include "commons/commons.h"
#include "commons/c_code.h"

class Argument : public Compileable {
    private:
        char flag_char;
        std::string *flag_name;
        std::string *help_desc;
        std::string *man_page;
        std::string *value_name;
        std::string *type;
        unsigned int pos;
    public:
        Argument(char flag_char,
                 std::string *flag_name,
                 std::string *help_desc,
                 std::string *man_page,
                 std::string *value_name,
                 std::string *type,
                 unsigned int pos);
        Argument(char flag_char,
                const char *flag_name,
                const char *help_desc,
                const char *man_page,
                const char *value_name,
                const char *type,
                unsigned int pos);
        ~Argument();

        void accept(Visitor *visitor);
};
