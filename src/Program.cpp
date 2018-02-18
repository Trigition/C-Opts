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
 * @param new_description The description for the program
 * @param new_man_page The man page for the program
 * @param new_version The program version
 */
Program::Program(std::string &name,
                 std::string &new_description,
                 std::string &new_man_page,
                 std::string &new_version) {
    this->name = name;
    this->description = new_description;
    this->man_page = new_man_page;
    this->version = new_version;
}

/**
 * Another constructor for the Program class but allows
 * passing of references to string literals.
 */
Program::Program(c_str &name,
                 c_str &new_description,
                 c_str &new_man_page,
                 c_str &new_version) {
    this->name = name;
    this->description = new_description;
    this->man_page = new_man_page;
    this->version = new_version;
}

/**
 * The main destructor for the Program class.
 */
Program::~Program() {
    //delete this->description;
    //delete this->man_page;
    //delete this->version;
}

/**
 * @brief This method adds a global argument to the
 * Program.
 * @param arg A reference to the argument being added
 */
void Program::add_global_arg(Argument &arg) {
    this->global_args.push_back(&arg);
}

/**
 * @brief This method adds an action to the Program.
 * @param action A reference to the action
 */
void Program::add_action(Action &action) {
    this->actions.push_back(&action);
}

/**
 * @brief This method accepts a Visitor class
 * @param visitor A reference to a Visitor.
 */
void Program::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
