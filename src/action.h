#pragma once

#include "commons/commons.h"
#include "argument.h"

class Action : public Compileable {
    private:
        std::string *action_name;
        std::string *action_desc;
    public:
        Action(std::string *action_name, std::string *action_desc);
        Action(const char *action_name, const char *action_desc);
        ~Action();

        void accept(Visitor *visitor);
};
