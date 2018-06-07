/**
 * @file Compiler.h
 * @author William Fong
 * @date 2018-02-15
 * @version 0.0.1
 *
 * @brief This is the header file for the Compiler Class
 * @section DESCRIPTION
 *
 * This header file puts definitions for the Compiler Class
 * and its functions and members.
 */
#pragma once
#include <map>
#include <cstdlib>
#include <fstream>
#include "../commons/ArgFile.h"
#include "../commons/Parameter.h"
#include "../commons/CodeBlock.h"
#include "../commons/Function.h"
#include "../commons/ArgStruct.h"
#include "../Program.h"
#include "../Argument.h"
#include "../Action.h"

typedef std::pair<Compileable *, HeaderFile *> headerPair;
typedef std::pair<Compileable *, SourceFile *> sourcePair;

/**
 * @brief This class compiles the Program argument
 */
class Compiler : public Visitor {
    private:
        Action *actionContext; // The current top global action tree branch
        Program *programContext; // The current program
        Compileable *currentContext;

        // Mapping of arguments, actions, and programs to files
        std::vector<ArgFile *> files;
        std::map<Defineable  *, HeaderFile *> headerMap;
        std::map<Compileable *, SourceFile *> sourceMap;

        std::string argDirectory; // The base argument directory for file output
        std::vector<std::string*> headerBuffer; // A buffer for header code
        std::vector<std::string*> sourceBuffer; // A buffer for source code
        bool debugMode;
        bool verboseMode;

        std::map<Program*, Argument*> globalArgs; // Arguments for a Program
        std::map<Action*, std::string> currentArgs; // Arguments for the current Action
        void createSwitch(std::string &name,
                std::vector<Argument*> &args,
                std::vector<Action*> &actions);
        void openContext(Action *action);
        void openContext(Program *program);

    public:
        Compiler(std::string &argDirectory);
        Compiler(c_str &argDirectory);
        ~Compiler();

        void dispatch(Parameter *parameter);
        void dispatch(CodeBlock *codeblock);
        void dispatch(Function *function);

        void dispatch(Program *program);
        void dispatch(Action *action);
        void dispatch(Argument *argument);

        void dispatch(ArgStruct *argStruct);

        void writeAllFiles();

        void debugLog(std::string mesg);
        void debugLog(c_str &mesg);
};
