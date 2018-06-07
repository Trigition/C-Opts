/**
 * @file Action.h
 * @author William Fong
 * @date 2018-02-15
 * @version 0.0.1
 *
 * @brief This is the header file for the Action Class
 * @section DESCRIPTION
 *
 * This header file puts definitions for the Action 
 * Class and its functions and members.
 */
#pragma once

#include "commons/Commons.h"
#include "Argument.h"

/**
 * @brief This class encompases a program action.
 * Actions are different methods of execution for a 
 * program. e.g The difference of functionality
 * between git add and git commit. There 'add' and
 * 'commit' would be different actions of the 
 * program 'git'.
 */
class Action : public Compileable {
    private:
        std::string actionName;
        std::string actionDesc;
        std::vector<Argument *> actionArguments;
        std::vector<Action *> subactions;
    public:
        Action(std::string &actionName, std::string &actionDesc);
        Action(const char &actionName, const char &actionDesc);
        ~Action();

        void addArgument(Argument &argument);
        void addSubaction(Action &subaction);

        // Getters
        std::string &getName() { return this->actionName; };
        std::string &getDesc() { return this->actionDesc; };
        std::vector<Argument*> &getArguments() { return this->actionArguments; };
        std::vector<Action*> &getSubactions() { return this->subactions; };

        void accept(Visitor &visitor);

        virtual void composeDefinition() override;
        virtual void composeSource() override;
};
