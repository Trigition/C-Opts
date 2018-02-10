#pragma once
#include <map>
#include "../commons/C_Code.h"

class Compiler : public Visitor {
    private:
        Action *action_context;
        bool debug_mode;
        bool verbose_mode;

        std::map<Program*, Argument*> global_args;
        std::map<Action*, std::string> current_args;

    public:
        Compiler();
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
