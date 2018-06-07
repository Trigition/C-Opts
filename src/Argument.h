/**
 * @file Argument.h
 * @author William Fong
 * @date 2018-02-15
 * @version 0.0.1
 *
 * @brief This is the header file for the Argument Class
 * @section DESCRIPTION
 *
 * This header file puts definitions for the Argument Class
 * and its functions and members.
 */
#pragma once

#include "commons/Commons.h"
#include "commons/C_Code.h"
#include "commons/Parameter.h"
#include "parsers/primitiveParsers.h"

/**
 * @brief This function encompases program Arguments.
 * Arguments are specific input parameters for a Program.
 * e.g Verbosity flags, filenames, input strings, etc are
 * specific Arguments which are passed in from the commandline.
 */
class Argument : public Compileable, public TypedInterface {
    private:
        char flagChar; // A shorthand flag e.g '-v' for '--verbose'
        std::string flagName; // The flag name verbose for '--verbose'
        std::string helpDesc; // The argument description for help output
        std::string manPage; // The manpage description for the argument
        std::string valueName; // The value name for C code interfaces
        unsigned int pos; // The nth position of the argument

        Function *parserFunction; // The function that will parse the argument

        void createFunction();

    public:
        Argument();
        Argument(char flagChar,
                 std::string &flagName,
                 std::string &helpDesc,
                 std::string &manPage,
                 std::string &valueName,
                 std::string &type,
                 unsigned int pos);
        Argument(char flagChar,
                 c_str &flagName,
                 c_str &helpDesc,
                 c_str &manPage,
                 c_str &valueName,
                 c_str &type,
                 unsigned int pos);
        ~Argument();

        void composeDefinition();
        void composeSource();

        // Setters
        void setChar(char flagChar) { this->flagChar = flagChar; };

        void setName(std::string &flagName) { this->flagName = flagName; };
        void setName(c_str &flagName) { this->flagName = flagName; };

        void setHelpDesc(std::string &helpDesc) {
            this->helpDesc = helpDesc;
        };
        void setHelpDesc(c_str &helpDesc) {
            this->helpDesc = helpDesc;
        };

        void setManPage(std::string &manPage) { this->manPage = manPage; };
        void setManPage(c_str &manPage) { this->manPage = manPage; };

        void setValueName(std::string &valueName) {
            this->valueName = valueName;
        };
        void setValueName(c_str &valueName) {
            this->valueName = valueName;   
        };

        void setPosition(unsigned int pos) { this->pos = pos; };

        // Getters
        char get_flagChar() { return this->flagChar; };
        std::string& getFlagName() { return this->flagName; };
        std::string& getHelpDesc() { return this->helpDesc; };
        std::string& getManPage() { return this->manPage; };
        std::string& getValueName() { return this->valueName; };
        unsigned int getPosition() { return this->pos; };

        Function *getFunction() { return this->parserFunction; };

        std::string *make_header();
        void accept(Visitor &visitor);
};

/**
 * @brief This class represents positionless Arguments or 'flags'
 * Flags are, in C-Opts, considered positionless flags. For example
 * a verbosity flag '-v' or '--verbose' doesn't have a position requirement.
 * It's equality valid to say $PROGRAM $ARG1 -v or $PROGRAM -v $ARG1. Both
 * will have the same meaning.
 */
class Flag : public Argument {
    public:
        Flag(char flagChar,
             std::string &flagName,
             std::string &helpDesc,
             std::string &manPage);
        Flag(char flagChar,
             c_str &flagName,
             c_str &helpDesc,
             c_str &manPage);
        ~Flag();
};

/**
 * @brief ValuedFlags are positionless flags that have values
 * assigned to them.
 */
class ValuedFlag : public Argument {
    public:
        ValuedFlag(char flagChar,
                   std::string &flagName,
                   std::string &helpDesc,
                   std::string &manPage,
                   std::string &valueName,
                   std::string &type);
        ValuedFlag(char flagChar,
                   c_str &flagName,
                   c_str &helpDesc,
                   c_str &manPage,
                   c_str &valueName,
                   c_str &type);
        ~ValuedFlag();
};
