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
#include "Parameter.h"

/**
 * @brief This is the constructor for the Parameter class
 * @param type The type of the input parameter
 * @param varName The variable name of the parameter
 */
Parameter::Parameter(std::string &type, std::string &varName) {
    this->setType(type);
    this->varName = varName;

    this->setParamString();
}

/**
 * @brief This is the constructor for the Parameter class
 * @param type The type of the input parameter
 * @param varName The variable name of the parameter
 */
Parameter::Parameter(c_str &type, c_str &varName) {
    this->setType(type);
    this->varName = varName;

    this->setParamString();
}

/**
 * This is the destructor for the Parameter class
 */
Parameter::~Parameter() {

}

void Parameter::setParamString() {
    this->paramString = this->getType() + " " +  this->getVarName();
}

/**
 * @brief This function compares a parameter's type with another
 * @param compar A reference to another parameter instance
 * @return Returns true if both parameters are the same type.
 */
bool Parameter::isSameType(Parameter &compar) {
    return this->getType() == compar.getType();
}

/**
 * @brief This function compares a parameter's name with another
 * @param compar A reference to another parameter instance
 * @return Returns true if both parameters have the same name.
 */
bool Parameter::isSameName(Parameter &compar) {
    return this->varName == compar.getVarName();
}

void Parameter::setVarName(std::string &varName) {
    this->varName = varName;
    this->setParamString();
}

void Parameter::setVarName(c_str &varName) {
    this->varName = varName;
    this->setParamString();
}
