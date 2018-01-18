#pragma once

#include "commons/Commons.h"
#include "commons/C_Code.h"

class Argument : public Compileable {
    private:
        char flag_char;
        std::string flag_name;
        std::string help_desc;
        std::string man_page;
        std::string value_name;
        std::string type;
        unsigned int pos;
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
                 const char* const &flag_name,
                 const char* const &help_desc,
                 const char* const &man_page,
                 const char* const &value_name,
                 const char* const &type,
                 unsigned int pos);
        ~Argument();

        // Setters
        void set_char(char flag_char) { this->flag_char = flag_char; };

        void set_name(std::string &flag_name) { this->flag_name = flag_name; };
        void set_name(const char* const &flag_name) { this->flag_name = flag_name; };

        void set_help_desc(std::string &help_desc) {
            this->help_desc = help_desc;
        };
        void set_help_desc(const char* const &help_desc) {
            this->help_desc = help_desc;
        };

        void set_man_page(std::string &man_page) { this->man_page = man_page; };
        void set_man_page(const char* const &man_page) { this->man_page = man_page; };

        void set_value_name(std::string &value_name) {
            this->value_name = value_name;
        };
        void set_value_name(const char* const &value_name) {
            this->value_name = value_name;   
        };

        void set_type(std::string &type) { this->type = type; };
        void set_type(const char* const &type) { this->type = type; };

        void set_position(unsigned int pos) { this->pos = pos; };

        // Getters
        char get_flag_char() { return this->flag_char; };
        std::string& get_flag_name() { return this->flag_name; };
        std::string& get_help_desc() { return this->help_desc; };
        std::string& get_man_page() { return this->man_page; };
        std::string& get_value_name() { return this->value_name; };
        std::string& get_type() { return this->type; };
        unsigned int get_position() { return this->pos; };

        std::string make_header();
        void accept(Visitor &visitor);
};

class Flag : public Argument {
    public:
        Flag(char flag_char,
             std::string &flag_name,
             std::string &help_desc,
             std::string &man_page);
        Flag(char flag_char,
             const char* const &flag_name,
             const char* const &help_desc,
             const char* const &man_page);
        ~Flag();
};

class ValuedFlag : public Argument {
    public:
        ValuedFlag(char flag_char,
                   std::string &flag_name,
                   std::string &help_desc,
                   std::string &man_page,
                   std::string &value_name,
                   std::string &type);
        ValuedFlag(char flag_char,
                   const char* const &flag_name,
                   const char* const &help_desc,
                   const char* const &man_page,
                   const char* const &value_name,
                   const char* const &type);
        ~ValuedFlag();
};
