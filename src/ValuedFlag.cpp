#include "argument.h"

ValuedFlag::ValuedFlag(char flag_char,
                       std::string &flag_name,
                       std::string &help_desc,
                       std::string &man_page,
                       std::string &value_name,
                       std::string &type) {
    this->set_char(flag_char);
    this->set_name(flag_name);
    this->set_help_desc(help_desc);
    this->set_man_page(man_page);
    this->set_value_name(value_name);
    this->set_type(type);

    this->set_position(0);
}

ValuedFlag::ValuedFlag(char flag_char,
                       const char* const &flag_name,
                       const char* const &help_desc,
                       const char* const &man_page,
                       const char* const &value_name,
                       const char* const &type) {
    this->set_char(flag_char);
    this->set_name(flag_name);
    this->set_help_desc(help_desc);
    this->set_man_page(man_page);
    this->set_value_name(value_name);
    this->set_type(type);

    this->set_position(0);

}

ValuedFlag::~ValuedFlag() {

}
