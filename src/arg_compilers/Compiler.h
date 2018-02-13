#pragma once
#include <map>
#include <cstdlib>
#include <fstream>
#include "../commons/C_Code.h"
#include "../Program.h"
#include "../Argument.h"
#include "../Action.h"

class Compiler : public Visitor {
    private:
        Action *action_context;
        Program *program_context;
        std::ofstream src_file_out;
        std::ofstream hdr_file_out;
        std::string arg_dir;
        bool debug_mode;
        bool verbose_mode;

        std::map<Program*, Argument*> global_args;
        std::map<Action*, std::string> current_args;
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

        void debug_log(std::string mesg);
        void debug_log(const char * const &mesg);
};
