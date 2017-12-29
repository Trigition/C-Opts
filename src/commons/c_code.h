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

extern class Program;
extern class Action;
extern class Argument;
// Begin Definitions
class Compileable {
    public:
        virtual void accept(Visitor *visitor) = 0;
}

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
        Parameter(std::string type, std::string var_name);
        Parameter(const char *type, const char *var_name);
        ~Parameter();
}

class CodeBlock : public Compileable {
    private:
        uchar depth;
        std::vector<std::string> code_lines;

    public:
        CodeBlock();
        ~CodeBlock();

        void add_line(std::string *line);
        void add_line(const char *line);

        // Visitor pattern
        void accept(Visitor *visitor);
};

class Function : public Compileable {
    private:
        std::string name;
        std::string return_type;
        std::vector<Parameter *> input_params;
        CodeBlock *function_code;

    public:
        Function(std::string name, std::string return_type);
        Function(const char *name, const char *return_type);
        ~Function();

        void add_input_param(Parameter *param);
        void add_code(CodeBlock *code);

        void accept(Visitor *visitor);
};
