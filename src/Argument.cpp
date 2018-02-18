/**
 * @file Argument.cpp
 * @author William Fong
 * @date 2018-02-16
 * @verion 0.0.1
 *
 * @brief This file is the source code for the class Argument
 * @section DESCRIPTION
 *
 * This source file contains all the implementation for Arguments
 */
#include "Argument.h"

/**
 * @brief Default constructor for an Argument
 * TODO Remove
 */
Argument::Argument() {

}

/**
 * @brief This is the main constructor for an Argument.
 * @param flag_char The single character shorthand e.g v for -v
 * @param flag_name The flag name. This is used for help printouts,
 * long hand names e.g --verbose. And for accessing the argument
 * @param help_desc The help description for the Argument.
 * @param value_name The name for the value being held by the
 * Argument. This is for help printouts as well as accessing
 * the value in your program.
 * @param type The datatype being stored
 * @param pos The position of the Argument
 */
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

/** @brief This is the main constructor but allows string
 * literals to be passed as parameters.
 */
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

/**
 * This is the destructor for the Argument class
 */
Argument::~Argument() {

}

/**
 * @brief This function constructs the header declarations
 * required by the Argument.
 * TODO IMPLEMENT
 */
std::string Argument::make_header() {
    
}

/**
 * @brief Acceptor function for compilation and other visitor
 * patterns
 * @param visitor A reference to a Visitor class
 */
void Argument::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
