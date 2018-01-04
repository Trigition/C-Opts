#pragma once

#include "argument.h"
#include "action.h"
class Program : public Compileable {
    private:
        std::string *description;
        std::string *man_page;
        std::string *version;
        std::vector<Argument> global_args;
        std::vector<Action> actions;

    public:
        Program(std::string *new_description, std::string *new_man_page, std::string *new_version);
        Program(const char *description, const char *man_page, const char *version);
        ~Program();

        void add_global_arg(Argument *arg);
        void add_action(Action *action);

        void accept(Visitor *visitor);
};
