/**
 * @file Function.cpp
 * @author William Fong
 * @date 2018-02-18
 * @version 0.0.1
 *
 * @brief This file is the source code for the Function class
 * @section DESCRIPTION
 *
 * This source file contains all of the code implementation for Functions
 */
#include "Function.h"

/**
 * @brief This is the main constructor for Functions
 * @param name The name of the function
 * @param return_type The type of the function
 */
Function::Function(std::string &name, std::string &return_type) {
    this->name = name;
    //this->return_type = return_type;
    this->setType(return_type);
    this->function_code = nullptr;
}

/**
 * @brief This is the main constructor for Function
 * @param name The name of the function
 * @param return_type The type of the function
 */
Function::Function(c_str &name, c_str &return_type) {
    this->name = name;
    this->setType(return_type);
    this->function_code = nullptr;
}

/**
 * The main destructor for the function. This will
 * remove the various parameters and code block 
 * associated with the Function.
 */
Function::~Function() {
    for (Parameter *p : this->input_params) {
        delete p;
    }

    if (this->function_code != nullptr) {
        delete this->function_code;
    }
}

/**
 * @brief This function ensures that a Function will
 * have a codeblock.
 */
void Function::ensure_codeblock_exists() {
    if (this->function_code == nullptr) {
        this->function_code = new CodeBlock();
        this->function_code->set_depth(1);
    }
}

/**
 * @brief This function adds an input Parameter to the
 * Function.
 * @param A reference to the new Parameter
 */
void Function::add_input_param(Parameter *param) {
    this->input_params.push_back(param);
}

/**
 * @brief This method adds a line of code to the
 * Function's CodeBlock.
 * @param code The new line of code
 */
void Function::add_codeline(std::string &code) {
    this->ensure_codeblock_exists();
    this->function_code->add_line(code);
}

/**
 * @brief This method adds a line of code to the
 * Function's CodeBlock.
 * @param code The new line of code
 */
void Function::add_codeline(c_str &code) {
    this->ensure_codeblock_exists();
    this->function_code->add_line(code);
}

void Function::composeDefinition() {
    std::string definition = this->getType();
    definition += " " + this->name;
    definition += "(";

    for (unsigned int i = 0; i < this->input_params.size() - 1; i++) {
        definition += this->input_params[i]->getParamString();
        definition += ", ";
    }
    definition += this->input_params[this->input_params.size() - 1]->getParamString();
    definition += ")";

    this->setDefinition(definition);
}

void Function::composeSource() {
    std::string code = "";
    code += this->getDefinition() + " {\n";
    for (std::string *lineOfCode : this->function_code->getCode()) {
        code += "    " + *lineOfCode + ";\n";
    }
    code += "}\n";
    this->setSource(code);
}

void Function::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
