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
 * @param flagChar A single character flag
 * @param flagName A long-hand flag name
 * @param helpDesc The help description
 * @param manPage The man page description
 * @param valueName How the value should be named
 * @param type The type for the value
 */
ValuedFlag::ValuedFlag(char flagChar,
                       std::string &flagName,
                       std::string &helpDesc,
                       std::string &manPage,
                       std::string &valueName,
                       std::string &type) {
    this->setChar(flagChar);
    this->setName(flagName);
    this->setHelpDesc(helpDesc);
    this->setManPage(manPage);
    this->setValueName(valueName);
    this->setType(type);

    this->setPosition(0);
}

/**
 * A constructor for ValuedFlags but allows passing of string literals
 */
ValuedFlag::ValuedFlag(char flagChar,
                       c_str &flagName,
                       c_str &helpDesc,
                       c_str &manPage,
                       c_str &valueName,
                       c_str &type) {
    this->setChar(flagChar);
    this->setName(flagName);
    this->setHelpDesc(helpDesc);
    this->setManPage(manPage);
    this->setValueName(valueName);
    this->setType(type);

    this->setPosition(0);

}

/**
 * The destructor for the ValuedFlag
 */
ValuedFlag::~ValuedFlag() {

}
