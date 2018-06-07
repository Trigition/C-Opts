/**
 * @file ArgStruct.h
 * @author William Fong
 * @date 2018-05-04
 * @version 0.0.1
 */

#pragma once

#include "C_Code.h"
#include "CodeBlock.h"
#include "../Argument.h"
#include "../Action.h"
#include "../Program.h"

class ArgStruct : public Defineable {
    private:
        std::vector<Argument *> arguments;
        std::string name;

        void loadArguments(std::vector<Argument *>& args);

    public:
        ArgStruct(Action *context);
        ArgStruct(Program *context);
        ~ArgStruct();

        void addArgument(Argument *arg);
        void accept(Visitor &visitor); 
        void composeDefinition();
};
