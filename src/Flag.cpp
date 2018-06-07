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
 * @param flagChar The single character flag
 * @param flagName The long flag name
 * @param helpDesc The help description for the flag
 * @param manPage The man page for the flag
 */
Flag::Flag(char flagChar,
           std::string &flagName,
           std::string &helpDesc,
           std::string &manPage) {

    this->setChar(flagChar);
    this->setName(flagName);
    this->setHelpDesc(helpDesc);
    this->setManPage(manPage);

    this->setValueName("");
    this->setType("");
    this->setPosition(0);
}

/**
 * @brief This is the constructor for flags but using C string literals
 */
Flag::Flag(char flagChar,
           const char* const &flagName,
           const char* const &helpDesc,
           const char* const &manPage) {

    this->setChar(flagChar);
    this->setName(flagName);
    this->setHelpDesc(helpDesc);
    this->setManPage(manPage);

    this->setValueName("");
    this->setType("");
    this->setPosition(0);
}

Flag::~Flag() {

}
