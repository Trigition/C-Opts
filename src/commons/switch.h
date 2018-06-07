/**
 * @file switch.h
 * @author William Fong
 * @date 2018-3-22
 * @version 0.0.1
 *
 * This file holds the construction of a C
 * switch statement
 */
#pragma once

#include "../C_Code.h"

class SwitchStatement : public Compileable {
    private:
        std::vector<std::string *> values;
        std::map<std::string, CodeBlock *> statementMap;
    public:
        SwitchStatement();
        ~SwitchStatement();

        void add_mapping(std::string &value, CodeBlock &behavior);
        void accept(Visitor &visitor);
};
