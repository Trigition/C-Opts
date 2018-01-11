#pragma once

#include "commons.h"

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
class Compileable {
    public:
        virtual void accept(Visitor &visitor) = 0;
};

class Visitor {
    public:
        virtual void dispatch(Parameter *parameter) = 0;
        virtual void dispatch(CodeBlock *codeblock) = 0;
        virtual void dispatch(Function *function) = 0;

        virtual void dispatch(Program *program) = 0;
        virtual void dispatch(Action *action) = 0;
        virtual void dispatch(Argument *argument) = 0;
};

class Parameter : public Compileable {
    private:
        std::string type;
        std::string var_name;

    public:
        Parameter(std::string &type, std::string &var_name);
        Parameter(const char &type, const char &var_name);

        bool is_same_type(Parameter &compar);
        bool is_same_name(Parameter &compar);

        //Setters
        void set_type(std::string &type) { this->type = type; };
        void set_type(const char &type) { this->type = type; };

        void set_var_name(std::string &var_name) { this->var_name = var_name; };
        void set_var_name(const char &var_name) { this->var_name = var_name; };

        // Getters
        std::string& get_type() { return this->type; };
        std::string& get_var_name() { return this->var_name; };

        ~Parameter();

        void accept(Visitor &visitor);
};

class CodeBlock : public Compileable {
    private:
        uchar depth;
        std::vector<std::string *> code_lines;

    public:
        CodeBlock();
        ~CodeBlock();

        void add_line(std::string &line);
        void add_line(const char &line);

        // Setters
        void set_depth(uchar depth) { this->depth = depth; };

        // Getters
        uchar get_depth() { return this->depth; };

        // Visitor pattern
        void accept(Visitor &visitor);
};

class Function : public Compileable {
    private:
        std::string name;
        std::string return_type;
        std::vector<Parameter *> input_params;
        CodeBlock *function_code;

        void ensure_codeblock_exists();

    public:
        Function(std::string &name, std::string &return_type);
        Function(const char &name, const char &return_type);
        ~Function();

        void add_input_param(Parameter &param);
        void set_code_block(CodeBlock &code);
        void add_codeline(std::string &code);
        void add_codeline(const char &code);

        void accept(Visitor &visitor);
};
