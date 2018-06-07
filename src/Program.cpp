/**
 * @file Program.cpp
 * @author William Fong
 * @date 2018-02-18
 * @version 0.0.1
 *
 * @brief This file is the source code for the Program class
 * @section DESCRIPTION
 *
 * This source file contains all of the code implementation for Programs.
 */
#include "Program.h"
/**
 * @brief This function is the constructor for the Program class
 * @param name A reference to the program name
 * @param description The description for the program
 * @param manPage The man page for the program
 * @param version The program version
 */
Program::Program(std::string &name,
                 std::string &description,
                 std::string &manPage,
                 std::string &version) {
    this->name = name;
    this->description = description;
    this->manPage = manPage;
    this->version = version;
}

/**
 * Another constructor for the Program class but allows
 * passing of references to string literals.
 */
Program::Program(c_str &name,
                 c_str &description,
                 c_str &manPage,
                 c_str &version) {
    this->name = name;
    this->description = description;
    this->manPage = manPage;
    this->version = version;
}

/**
 * The main destructor for the Program class.
 */
Program::~Program() {

}

/**
 * @brief This method adds a global argument to the
 * Program.
 * @param arg A reference to the argument being added
 */
void Program::addGlobalArg(Argument &arg) {
    this->globalArgs.push_back(&arg);
}

/**
 * @brief This method adds an action to the Program.
 * @param action A reference to the action
 */
void Program::addAction(Action &action) {
    this->actions.push_back(&action);
}

/**
 * @brief This method accepts a Visitor class
 * @param visitor A reference to a Visitor.
 */
void Program::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
