#pragma once

#include "Argument.h"
#include "Action.h"

class Program : public Compileable {
    private:
        std::string name;
        std::string description;
        std::string man_page;
        std::string version;
        std::vector<Argument*> global_args;
        std::vector<Action*> actions;

    public:
        Program(std::string &name,
                std::string &new_description,
                std::string &new_man_page,
                std::string &new_version);

        Program(c_str &name,
                c_str &description,
                c_str &man_page,
                c_str &version);
        ~Program();

        void add_global_arg(Argument &arg);
        void add_action(Action &action);

        void accept(Visitor &visitor);

        // Setters
        void set_description(std::string &desc) { this->description = desc; };
        void set_description(c_str &desc) {
            this->description = desc;
        };
        void set_man_page(std::string &man_page) { this->man_page = man_page; };
        void set_man_page(c_str &man_page) {
            this->man_page = man_page;
        };
        void set_version(std::string &version) { this->version = version; };
        void set_version(c_str &version) {
            this->version = version;
        };
        // Getters
        std::string &get_name() { return this->name; };
        std::string &get_description() { return this->description; };
        std::string &get_man_page() { return this->man_page; };
        std::string &get_version() { return this->version; };
        std::vector<Argument*> &get_args() { return this->global_args; };
        std::vector<Action*> &get_actions() { return this->actions; };
};
