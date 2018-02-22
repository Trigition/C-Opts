/**
 * @file C_Code.h
 * @author William Fong
 * @date 2018-02-19
 * @version 0.0.1
 *
 * @TODO Split this file into separate header files for
 * readability
 */
#pragma once

#include "Commons.h"

// Define formatting options
typedef enum {
    KR,
    Allman,
    GNU,
    Whitesmiths,
    Horstmann,
    Pico,
    Ratliff,
    Lisp
} indent_style;

// Begin Forward Declarations
class Dispatch;
class Parameter;
class CodeBlock;
class Function;

class Program;
class Action;
class Argument;
class Visitor;

// Begin Definitions
// Base Class for accepting Visitors
class Compileable {
    public:
        virtual void accept(Visitor &visitor) = 0;
};

// Abstract Visitor Class for Visitor Pattern
class Visitor {
    public:
        virtual void dispatch(Parameter *parameter) = 0;
        virtual void dispatch(CodeBlock *codeblock) = 0;
        virtual void dispatch(Function *function) = 0;

        virtual void dispatch(Program *program) = 0;
        virtual void dispatch(Action *action) = 0;
        virtual void dispatch(Argument *argument) = 0;
};

// Defines a Code Parameter
class Parameter : public Compileable {
    private:
        std::string type;
        std::string var_name;

    public:
        Parameter(std::string &type, std::string &var_name);
        Parameter(c_str &type, c_str &var_name);
        ~Parameter();

        bool is_same_type(Parameter &compar);
        bool is_same_name(Parameter &compar);

        //Setters
        void set_type(std::string &type) { this->type = type; };
        void set_type(c_str &type) { this->type = type; };

        void set_var_name(std::string &var_name) { this->var_name = var_name; };
        void set_var_name(c_str &var_name) { this->var_name = var_name; };

        // Getters
        std::string& get_type() { return this->type; };
        std::string& get_var_name() { return this->var_name; };
        std::string get_definition() { return this->get_type() + this->get_var_name(); };

        void accept(Visitor &visitor);
};

class CodeBlock : public Compileable {
    private:
        uchar depth;
        std::vector<std::string *> code_lines;
        std::string statement_delimiter;

    public:
        CodeBlock();
        ~CodeBlock();

        void add_line(std::string &line);
        void add_line(c_str &line);

        // Setters
        void set_depth(uchar depth) { this->depth = depth; };
        void set_statement_delimiter(std::string &delim) {
            this->statement_delimiter = delim;
        };
        void set_statement_delimiter(c_str &delim) {
            this->statement_delimiter = delim;
        }

        // Getters
        uchar get_depth() { return this->depth; };
        std::string get_statement_delimiter() { return this->statement_delimiter; };
        std::string *get_code();

        // Visitor pattern
        void accept(Visitor &visitor);
};

class Function : public Compileable {
    private:
        std::string name;
        std::string return_type;
        std::string header;
        std::vector<Parameter *> input_params;
        CodeBlock *function_code;

        void ensure_codeblock_exists();

    public:
        Function(std::string &name, std::string &return_type);
        Function(c_str &name, c_str  &return_type);
        ~Function();

        void add_input_param(Parameter *param);
        void set_code_block(CodeBlock &code);
        void add_codeline(std::string &code);
        void add_codeline(c_str &code);

        std::string &gen_function_header();
        std::vector<std::string *> &get_code();

        void accept(Visitor &visitor);
};
