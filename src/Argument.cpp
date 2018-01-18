#include "Argument.h"

Argument::Argument() {

}

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
                   const char* const &flag_name,
                   const char* const &help_desc,
                   const char* const &man_page,
                   const char* const &value_name,
                   const char* const &type,
                   unsigned int pos) {
    this->flag_name = flag_name;
    this->help_desc = help_desc;
    this->man_page = man_page;
    this->value_name = value_name;
    this->type = type;
    this->pos = pos;
}

Argument::~Argument() {

}

std::string Argument::make_header() {
    
}

void Argument::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
