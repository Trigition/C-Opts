#pragma once

#include "Argument.h"
#include "Action.h"

class Program : public Compileable {
    private:
        std::string description;
        std::string man_page;
        std::string version;
        std::vector<Argument*> global_args;
        std::vector<Action*> actions;

    public:
        Program(std::string &new_description, std::string &new_man_page, std::string &new_version);
        Program(const char* const &description,
                const char* const &man_page,
                const char* const &version);
        ~Program();

        void add_global_arg(Argument &arg);
        void add_action(Action &action);

        void accept(Visitor &visitor);

        // Setters
        void set_description(std::string &desc) { this->description = desc; };
        void set_description(const char* const &desc) {
            this->description = desc;
        };
        void set_man_page(std::string &man_page) { this->man_page = man_page; };
        void set_man_page(const char* const &man_page) {
            this->man_page = man_page;
        };
        void set_version(std::string &version) { this->version = version; };
        void set_version(const char * const &version) {
            this->version = version;
        };
        // Getters
        std::string &get_description() { return this->description; };
        std::string &get_man_page() { return this->man_page; };
        std::string &get_version() { return this->version; };
        std::vector<Argument*> &get_global_args() { return this->global_args; };
        std::vector<Action*> &get_actions() { return this->actions; };
};
