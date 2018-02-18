/**
 * @file Flag.cpp
 * @author William Fong
 * @date 2018-02-18
 * @version 0.0.1
 *
 * @brief This file is the source code for Flags
 * @section DESCRIPTION
 *
 * This source file contains all of the code implementation for Flags.
 */
#include "Argument.h"

/**
 * @brief This is the constructor for flags
 * @param flag_char The single character flag
 * @param flag_name The long flag name
 * @param help_desc The help description for the flag
 * @param man_page The man page for the flag
 */
Flag::Flag(char flag_char,
           std::string &flag_name,
           std::string &help_desc,
           std::string &man_page) {

    this->set_char(flag_char);
    this->set_name(flag_name);
    this->set_help_desc(help_desc);
    this->set_man_page(man_page);

    this->set_value_name("");
    this->set_type("");
    this->set_position(0);
}

/**
 * @brief This is the constructor for flags but using C string literals
 */
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
