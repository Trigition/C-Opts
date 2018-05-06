#pragma once

#include "C_Code.h"
#include "Parameter.h"
#include "CodeBlock.h"

class Function : public Compileable {
    private:
        std::string name;
        std::string return_type;
        std::string header;
        std::vector<Parameter *> input_params;
        CodeBlock *function_code;

        void ensure_codeblock_exists();

    public:
        Function(std::string &name, std::string &return_type);
        Function(c_str &name, c_str  &return_type);
        ~Function();

        void add_input_param(Parameter *param);
        void set_code_block(CodeBlock &code);
        void add_codeline(std::string &code);
        void add_codeline(c_str &code);

        std::string &gen_function_header();
        std::vector<std::string *> &get_code();

        void accept(Visitor &visitor);
};
