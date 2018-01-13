#include "argument.h"

Flag::Flag(char flag_char,
           std::string &flag_name,
           std::string &help_desc,
           std::string &man_page) {
    //this->flag_char = flag_char;
    //this->flag_name = flag_name;
    //this->help_desc = help_desc;
    //this->man_page = help_desc;

    //this->value_name = "";
    //this->type = "";
    //this->pos = 0;

    this->set_char(flag_char);
    this->set_name(flag_name);
    this->set_help_desc(help_desc);
    this->set_man_page(man_page);

    this->set_value_name("");
    this->set_type("");
    this->set_position(0);
}

Flag::Flag(char flag_char,
           const char* const &flag_name,
           const char* const &help_desc,
           const char* const &man_page) {
    this->set_char(flag_char);
    this->set_name(flag_name);
    this->set_help_desc(help_desc);
    this->set_man_page(man_page);

    this->set_value_name("");
    this->set_type("");
    this->set_position(0);
}

Flag::~Flag() {

}
