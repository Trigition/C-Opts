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
#include "parsers/primitive_parsers.h"

/**
 * @brief This function encompases program Arguments.
 * Arguments are specific input parameters for a Program.
 * e.g Verbosity flags, filenames, input strings, etc are
 * specific Arguments which are passed in from the commandline.
 */
class Argument : public Compileable, public TypedInterface {
    private:
        char flag_char; // A shorthand flag e.g '-v' for '--verbose'
        std::string flag_name; // The flag name verbose for '--verbose'
        std::string help_desc; // The argument description for help output
        std::string man_page; // The manpage description for the argument
        std::string value_name; // The value name for C code interfaces
        unsigned int pos; // The nth position of the argument

        Function *parserFunction; // The function that will parse the argument

        void createFunction();

    public:
        Argument();
        Argument(char flag_char,
                 std::string &flag_name,
                 std::string &help_desc,
                 std::string &man_page,
                 std::string &value_name,
                 std::string &type,
                 unsigned int pos);
        Argument(char flag_char,
                 c_str &flag_name,
                 c_str &help_desc,
                 c_str &man_page,
                 c_str &value_name,
                 c_str &type,
                 unsigned int pos);
        ~Argument();

        void composeDefinition();
        void composeSource();

        // Setters
        void set_char(char flag_char) { this->flag_char = flag_char; };

        void set_name(std::string &flag_name) { this->flag_name = flag_name; };
        void set_name(c_str &flag_name) { this->flag_name = flag_name; };

        void set_help_desc(std::string &help_desc) {
            this->help_desc = help_desc;
        };
        void set_help_desc(c_str &help_desc) {
            this->help_desc = help_desc;
        };

        void set_man_page(std::string &man_page) { this->man_page = man_page; };
        void set_man_page(c_str &man_page) { this->man_page = man_page; };

        void set_value_name(std::string &value_name) {
            this->value_name = value_name;
        };
        void set_value_name(c_str &value_name) {
            this->value_name = value_name;   
        };

        void set_position(unsigned int pos) { this->pos = pos; };

        // Getters
        char get_flag_char() { return this->flag_char; };
        std::string& get_flag_name() { return this->flag_name; };
        std::string& get_help_desc() { return this->help_desc; };
        std::string& get_man_page() { return this->man_page; };
        std::string& get_value_name() { return this->value_name; };
        unsigned int get_position() { return this->pos; };

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
        Flag(char flag_char,
             std::string &flag_name,
             std::string &help_desc,
             std::string &man_page);
        Flag(char flag_char,
             c_str &flag_name,
             c_str &help_desc,
             c_str &man_page);
        ~Flag();
};

/**
 * @brief ValuedFlags are positionless flags that have values
 * assigned to them.
 */
class ValuedFlag : public Argument {
    public:
        ValuedFlag(char flag_char,
                   std::string &flag_name,
                   std::string &help_desc,
                   std::string &man_page,
                   std::string &value_name,
                   std::string &type);
        ValuedFlag(char flag_char,
                   c_str &flag_name,
                   c_str &help_desc,
                   c_str &man_page,
                   c_str &value_name,
                   c_str &type);
        ~ValuedFlag();
};
