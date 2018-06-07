#pragma once

#include "C_Code.h"
#include "Parameter.h"
#include "CodeBlock.h"


class Function : public Compileable, TypedInterface {

    private:
        std::string name;
        std::string returnType;
        std::vector<Parameter *> inputParams;
        CodeBlock *functionCode;

        void ensureCodeBlockExists();

    public:
        Function(std::string &name, std::string &returnType);
        Function(c_str &name, c_str  &returnType);
        ~Function();

        void addInputParam(Parameter *param);
        void setCodeBlock(CodeBlock &code);
        void addCodeline(std::string &code);
        void addCodeline(c_str &code);

        virtual void composeDefinition() override;
        virtual void composeSource() override;

        void accept(Visitor &visitor);
};
