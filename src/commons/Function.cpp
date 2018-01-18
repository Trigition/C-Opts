#include "C_Code.h"

Function::Function(std::string &name, std::string &return_type) {
    this->name = name;
    this->return_type = return_type;
    this->function_code = nullptr;
}

Function::Function(const char &name, const char &return_type) {
    this->name = name;
    this->return_type = return_type;
    this->function_code = nullptr;
}

Function::~Function() {
    for (Parameter *p : this->input_params) {
        delete p;
    }

    if (this->function_code != nullptr) {
        delete this->function_code;
    }
}

void Function::ensure_codeblock_exists() {
    if (this->function_code == nullptr) {
        this->function_code = new CodeBlock();
        this->function_code->set_depth(1);
    }
}

void Function::add_input_param(Parameter &param) {
    this->input_params.push_back(&param);
}

void Function::add_codeline(std::string &code) {
    this->ensure_codeblock_exists();
    this->function_code->add_line(code);
}

void Function::add_codeline(const char &code) {
    this->ensure_codeblock_exists();
    this->function_code->add_line(code);
}

std::string& Function::gen_function_header() {
    std::string new_header = "";
    new_header = this->name;
    new_header += "(";
 
    for (unsigned int i = 0; i < this->input_params.size() - 1; i++) {
        new_header += this->input_params[i]->get_definition();
        new_header += ", ";
    }

    new_header += this->input_params[this->input_params.size() - 1]->get_definition();
    new_header += ")";

    this->header = new_header;

    return this->header;
}

void Function::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
