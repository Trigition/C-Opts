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

class ArgStruct : public Compileable {
    private:
        std::vector<Argument *> arguments;
        std::string name;

        void load_arguments(std::vector<Argument *>& args);

    public:
        ArgStruct(Action *context);
        ArgStruct(Program *context);
        ~ArgStruct();

        void add_argument(Argument *arg);
        std::string *create_typedef();
        void accept(Visitor &visitor); 
};
