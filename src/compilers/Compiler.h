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
#include "../commons/Parameter.h"
#include "../commons/CodeBlock.h"
#include "../commons/Function.h"
#include "../commons/ArgStruct.h"
#include "../Program.h"
#include "../Argument.h"
#include "../Action.h"

/**
 * @brief This class compiles the Program argument
 */
class Compiler : public Visitor {
    private:
        Action *action_context; // The current top global action tree branch
        Program *program_context; // The current program
        std::ofstream src_file_out; // The current source file output
        std::ofstream hdr_file_out; // The current header file output
        std::string arg_dir; // The base argument directory for file output
        std::vector<std::string*> header_buffer; // A buffer for header code
        std::vector<std::string*> source_buffer; // A buffer for source code
        bool debug_mode;
        bool verbose_mode;

        std::map<Program*, Argument*> global_args; // Arguments for a Program
        std::map<Action*, std::string> current_args; // Arguments for the current Action
        void create_switch(std::string &name,
                std::vector<Argument*> &args,
                std::vector<Action*> &actions);
        void open_context(Action *action);
        void open_context(Program *program);

    public:
        Compiler(std::string &arg_dir);
        Compiler(c_str &arg_dir);
        ~Compiler();

        void dispatch(Parameter *parameter);
        void dispatch(CodeBlock *codeblock);
        void dispatch(Function *function);

        void dispatch(Program *program);
        void dispatch(Action *action);
        void dispatch(Argument *argument);

        void dispatch(ArgStruct *arg_struct);

        void debug_log(std::string mesg);
        void debug_log(c_str &mesg);
};
