#include "argument.h"

Argument::Argument(char flag_char,
                   std::string &flag_name,
                   std::string &help_desc,
                   std::string &man_page,
                   std::string &value_name,
                   std::string &type,
                   unsigned int pos) {
    this->flag_name = flag_name;
    this->help_desc = help_desc;
    this->man_page = man_page;
    this->value_name = value_name;
    this->type = type;
    this->pos = pos;
}

Argument::Argument(char flag_char,
                   const char &flag_name,
                   const char &help_desc,
                   const char &man_page,
                   const char &value_name,
                   const char &type,
                   unsigned int pos) {
    this->flag_name = flag_name;
    this->help_desc = help_desc;
    this->man_page = man_page;
    this->value_name = value_name;
    this->type = type;
    this->pos = pos;
}

Argument::~Argument() {
    //delete this->flag_name;
    //delete this->help_desc;
    //delete this->man_page;
    //delete this->value_name;
    //delete this->type;
}



void Argument::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
