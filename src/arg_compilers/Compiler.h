#pragma once
#include "../commons/C_Code.h"

class Compiler : public Visitor {
    private:
        Action *action_context;

    public:
        Compiler();
        ~Compiler();

        void dispatch(Parameter *parameter);
        void dispatch(CodeBlock *codeblock);
        void dispatch(Function *function);

        void dispatch(Program *program);
        void dispatch(Action *action);
        void dispatch(Argument *argument);
};
