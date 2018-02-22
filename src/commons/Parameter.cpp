/**
 * @file Parameter.cpp
 * @author William Fong
 * @date 2018-02-19
 * @version 0.0.1
 *
 * @brief This file is the source code for the Parameter class
 * @section DESCRIPTION
 *
 * This source file contains all the implementation for Parameters
 */
#include "C_Code.h"

/**
 * @brief This is the constructor for the Parameter class
 * @param type The type of the input parameter
 * @param var_name The variable name of the parameter
 */
Parameter::Parameter(std::string &type, std::string &var_name) {
    this->type = type;
    this->var_name = var_name;
}

/**
 * @brief This is the constructor for the Parameter class
 * @param type The type of the input parameter
 * @param var_name The variable name of the parameter
 */
Parameter::Parameter(c_str &type, c_str &var_name) {
    this->type = type;
    this->var_name = var_name;
}

/**
 * This is the destructor for the Parameter class
 */
Parameter::~Parameter() {

}

/**
 * @brief This function compares a parameter's type with another
 * @param compar A reference to another parameter instance
 * @return Returns true if both parameters are the same type.
 */
bool Parameter::is_same_type(Parameter &compar) {
    return this->type == compar.get_type();
}

/**
 * @brief This function compares a parameter's name with another
 * @param compar A reference to another parameter instance
 * @return Returns true if both parameters have the same name.
 */
bool Parameter::is_same_name(Parameter &compar) {
    return this->var_name == compar.get_type();
}

/**
 * @brief This function accepts a Visitor class
 * @param visitor A reference to the Visitor
 */
void Parameter::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
