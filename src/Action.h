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
        std::string action_name;
        std::string action_desc;
        std::vector<Argument *> action_arguments;
        std::vector<Action *> subactions;
    public:
        Action(std::string &action_name, std::string &action_desc);
        Action(const char &action_name, const char &action_desc);
        ~Action();

        void add_argument(Argument &argument);
        void add_subaction(Action &subaction);

        // Getters
        std::string &get_name() { return this->action_name; };
        std::string &get_desc() { return this->action_desc; };
        std::vector<Argument*> &get_arguments() { return this->action_arguments; };
        std::vector<Action*> &get_subactions() { return this->subactions; };

        void accept(Visitor &visitor);
};
