/**
 * @file Argument.cpp
 * @author William Fong
 * @date 2018-02-16
 * @version 0.0.1
 *
 * @brief This file is the source code for the class Argument
 * @section DESCRIPTION
 *
 * This source file contains all the implementation for Arguments
 */
#include "Argument.h"

Argument::Argument() {
    this->flagName = "UNSET";
    this->helpDesc = "UNSET";
    this->manPage = "UNSET";
    this->valueName = "UNSET";
    this->pos = -1;

    this->setType("UNSET");
    this->parserFunction == nullptr;
}

/**
 * @brief This is the main constructor for an Argument.
 * @param flagChar The single character shorthand e.g v for -v
 * @param flagName The flag name. This is used for help printouts,
 * long hand names e.g --verbose. And for accessing the argument
 * @param helpDesc The help description for the Argument.
 * @param valueName The name for the value being held by the
 * Argument. This is for help printouts as well as accessing
 * the value in your program.
 * @param type The datatype being stored
 * @param pos The position of the Argument
 */
Argument::Argument(char flagChar,
                   std::string &flagName,
                   std::string &helpDesc,
                   std::string &manPage,
                   std::string &valueName,
                   std::string &type,
                   unsigned int pos) {
    this->flagName = flagName;
    this->helpDesc = helpDesc;
    this->manPage = manPage;
    this->valueName = valueName;
    this->pos = pos;

    this->setType(type);
    this->parserFunction = nullptr;
}

/** @brief This is the main constructor but allows string
 * literals to be passed as parameters.
 */
Argument::Argument(char flagChar,
                   c_str &flagName,
                   c_str &helpDesc,
                   c_str &manPage,
                   c_str &valueName,
                   c_str &type,
                   unsigned int pos) {
    this->flagName = flagName;
    this->helpDesc = helpDesc;
    this->manPage = manPage;
    this->valueName = valueName;
    this->pos = pos;

    this->setType(type);
    this->parserFunction = nullptr;
}

Argument::~Argument() {
    if (this->parserFunction != nullptr) {
        delete this->parserFunction;
    }
}

void Argument::createFunction() {
    std::string funcName = this->getFlagName() + "_arg_parser";
    Function* parserFunction = PrimitiveParsers::getParser(funcName, this->getType());
    this->parserFunction = parserFunction;

}

void Argument::composeDefinition() {
    std::string def = this->getType() + " " + this->getFlagName();
    this->setDefinition(def);  
}

void Argument::composeSource() {
}

/**
 * @brief This function constructs the header declarations
 * required by the Argument.
 * TODO IMPLEMENT
 */
std::string *Argument::make_header() {
    return new std::string("NO HEADER FOR " + this->getFlagName() + "\n");
}

/**
 * @brief Acceptor function for compilation and other visitor
 * patterns
 * @param visitor A reference to a Visitor class
 */
void Argument::accept(Visitor &visitor) {
    this->createFunction();
    visitor.dispatch(this);
}
