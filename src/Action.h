#pragma once

#include "commons/Commons.h"
#include "Argument.h"

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
