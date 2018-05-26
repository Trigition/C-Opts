/**
 * @file Program.h
 * @author William Fong
 * @date 2018-02-15
 * @version 0.0.1
 *
 * @brief This is the header for the Program Class
 * @section DESCRIPTION
 *
 * This header file puts definitions for the Program Class
 * and its functions and members.
 */
#pragma once

#include "Argument.h"
#include "Action.h"

/**
 * @brief This class encompases individual programs.
 * Programs are separate executables that C-Opts generates
 * argument parsers for.
 */
class Program : public Compileable {
    private:
        std::string name; // The name of the program
        std::string description; // The description of the program
        std::string man_page; // The man page description
        std::string version; // The version of the program
        std::vector<Argument*> global_args; // Global arguments
        std::vector<Action*> actions; // Main program actions

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
        void composeDefinition() {

        }

        void composeSource() {

        }

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
