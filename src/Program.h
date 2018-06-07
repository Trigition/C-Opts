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
        std::string manPage; // The man page description
        std::string version; // The version of the program
        std::vector<Argument*> globalArgs; // Global arguments
        std::vector<Action*> actions; // Main program actions

    public:
        Program(std::string &name,
                std::string &description,
                std::string &manPage,
                std::string &version);

        Program(c_str &name,
                c_str &description,
                c_str &manPage,
                c_str &version);
        ~Program();

        void addGlobalArg(Argument &arg);
        void addAction(Action &action);

        void accept(Visitor &visitor);
        void composeDefinition() {

        }

        void composeSource() {

        }

        // Setters
        void setDescription(std::string &desc) { this->description = desc; };
        void setDescription(c_str &desc) {
            this->description = desc;
        };
        void setManPage(std::string &manPage) { this->manPage = manPage; };
        void setManPage(c_str &manPage) {
            this->manPage = manPage;
        };
        void setVersion(std::string &version) { this->version = version; };
        void setVersion(c_str &version) {
            this->version = version;
        };
        // Getters
        std::string &getName() { return this->name; };
        std::string &getDescription() { return this->description; };
        std::string &getManPage() { return this->manPage; };
        std::string &getVersion() { return this->version; };
        std::vector<Argument*> &getArgs() { return this->globalArgs; };
        std::vector<Action*> &getActions() { return this->actions; };
        
};
