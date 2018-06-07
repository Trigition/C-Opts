/**
 * @file Action.cpp
 * @author William Fong
 * @date 2018-02-16
 * @version 0.0.1
 *
 * @brief This file is the source code for the class Action
 * @section DESCRIPTION
 *
 * This source file contains all of the code implementation for Actions.
 */
#include "Action.h"

/**
 * @brief This function is the main constructor for the Action class
 * @param actionName The name for the action
 * @param actionDesc The description for the action
 * @return An Action instance
 */
Action::Action(std::string &actionName, std::string &actionDesc) {
    this->actionName = actionName;
    this->actionDesc = actionDesc;
}

/**
 * @brief This the destructor for the Action class.
 * This destructor will remove the Action instance as
 * well as any Arguments attached to the instance. The
 * destructor will also free any subactions.
 */
Action::~Action() {
    //delete this->actionName;
    //delete this->actionDesc;
    for (Argument *a : this->actionArguments) {
        delete a;
    }

    for (Action *a : this->subactions) {
        delete a;
    }
}

/**
 * @brief This function adds an argument to an Action.
 * @param argument A reference to the argument to be added.
 */
void Action::addArgument(Argument &argument) {
    this->actionArguments.push_back(&argument);
}

/**
 * @brief This function adds an action to be a subaction.
 * @param subaction A reference to the subaction.
 */
void Action::addSubaction(Action &subaction) {
    this->subactions.push_back(&subaction);
}

/**
 * @brief This function accepts a Visitor class for double dispatch
 * @param visitor A reference to a Visitor instance
 */
void Action::accept(Visitor &visitor) {
    visitor.dispatch(this);
}

void Action::composeDefinition() {

}

void Action::composeSource() {

}
