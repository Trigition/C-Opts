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

class ArgStruct;

class Visitor;

// Begin Definitions
// Base Class for accepting Visitors
class Compileable {
    public:
        virtual void accept(Visitor &visitor) = 0;
        virtual std::string *compose_string() = 0;
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

        virtual void dispatch(ArgStruct *arg_struct) = 0;
};
