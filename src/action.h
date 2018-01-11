#pragma once

#include "commons/commons.h"
#include "argument.h"

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

        void accept(Visitor &visitor);
};
