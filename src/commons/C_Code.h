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

class TypedInterface {
    private:
        std::string type;
        static bool isInVector(std::string &type, std::vector<std::string> &vector);

    public:
        TypedInterface(){};
        ~TypedInterface(){};
        std::string &getType() { return this->type; };
        void setType(std::string &type) { this->type = getTypeAlias(type); };
        void setType(c_str &type) { this->type = getTypeAlias(type); };
        // TODO At some point have this lookup map be created at
        // compile time
        static std::string getTypeAlias(std::string &type);
        static std::string getTypeAlias(c_str &type);
};

class Defineable {
    private:
        std::string definition;

    public:
        Defineable(){};
        virtual ~Defineable(){};
        virtual void accept(Visitor &visitor) = 0;
        virtual void composeDefinition() = 0;
        void setDefinition(std::string &def) { this->definition = def; };
        void setDefinition(c_str &def) { this->definition = def; };

        std::string &getDefinition() {
            this->composeDefinition();
            return this->definition;
        };
};

// Begin Definitions
// Base Class for accepting Visitors
class Compileable : public Defineable {
    private:
        std::string source;

    public:
        Compileable(){};
        virtual ~Compileable(){};
        virtual void accept(Visitor &visitor) = 0;
        virtual void composeSource() = 0;

        void setSource(std::string &src) { this->source = src; };
        void setSource(c_str &src) { this->source = src; };
        std::string &getSource() {
            this->composeSource();
            return this->source;
        };
};

// Abstract Visitor Class for Visitor Pattern
class Visitor {
    public:
        Visitor(){};
        virtual ~Visitor(){};
        virtual void dispatch(Function *function) = 0;

        virtual void dispatch(Program *program) = 0;
        virtual void dispatch(Action *action) = 0;
        virtual void dispatch(Argument *argument) = 0;

        virtual void dispatch(ArgStruct *arg_struct) = 0;
};
