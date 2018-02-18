/**
 * @file ValuedFlag.cpp
 * @author William Fong
 * @date 2018-02-18
 * @version 0.0.1
 *
 * @brief This file is the source code for the class ValuedFlag
 * @section DESCRIPTION
 *
 * This source file contains all the implementation for ValuedFlags
 */
#include "Argument.h"

/**
 * @brief This is the main constructor for ValuedFlags.
 * @param flag_char A single character flag
 * @param flag_name A long-hand flag name
 * @param help_desc The help description
 * @param man_page The man page description
 * @param value_name How the value should be named
 * @param type The type for the value
 */
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

/**
 * A constructor for ValuedFlags but allows passing of string literals
 */
ValuedFlag::ValuedFlag(char flag_char,
                       c_str &flag_name,
                       c_str &help_desc,
                       c_str &man_page,
                       c_str &value_name,
                       c_str &type) {
    this->set_char(flag_char);
    this->set_name(flag_name);
    this->set_help_desc(help_desc);
    this->set_man_page(man_page);
    this->set_value_name(value_name);
    this->set_type(type);

    this->set_position(0);

}

/**
 * The destructor for the ValuedFlag
 */
ValuedFlag::~ValuedFlag() {

}
