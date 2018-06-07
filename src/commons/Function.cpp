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
 * @param returnType The type of the function
 */
Function::Function(std::string &name, std::string &returnType) {
    this->name = name;
    //this->returnType = returnType;
    this->setType(returnType);
    this->functionCode = nullptr;
}

/**
 * @brief This is the main constructor for Function
 * @param name The name of the function
 * @param returnType The type of the function
 */
Function::Function(c_str &name, c_str &returnType) {
    this->name = name;
    this->setType(returnType);
    this->functionCode = nullptr;
}

/**
 * The main destructor for the function. This will
 * remove the various parameters and code block 
 * associated with the Function.
 */
Function::~Function() {
    for (Parameter *p : this->inputParams) {
        delete p;
    }

    if (this->functionCode != nullptr) {
        delete this->functionCode;
    }
}

/**
 * @brief This function ensures that a Function will
 * have a codeblock.
 */
void Function::ensureCodeBlockExists() {
    if (this->functionCode == nullptr) {
        this->functionCode = new CodeBlock();
        this->functionCode->setDepth(1);
    }
}

/**
 * @brief This function adds an input Parameter to the
 * Function.
 * @param A reference to the new Parameter
 */
void Function::addInputParam(Parameter *param) {
    this->inputParams.push_back(param);
}

/**
 * @brief This method adds a line of code to the
 * Function's CodeBlock.
 * @param code The new line of code
 */
void Function::addCodeline(std::string &code) {
    this->ensureCodeBlockExists();
    this->functionCode->addLine(code);
}

/**
 * @brief This method adds a line of code to the
 * Function's CodeBlock.
 * @param code The new line of code
 */
void Function::addCodeline(c_str &code) {
    this->ensureCodeBlockExists();
    this->functionCode->addLine(code);
}

void Function::composeDefinition() {
    std::string definition = this->getType();
    definition += " " + this->name;
    definition += "(";

    for (unsigned int i = 0; i < this->inputParams.size() - 1; i++) {
        definition += this->inputParams[i]->getParamString();
        definition += ", ";
    }
    definition += this->inputParams[this->inputParams.size() - 1]->getParamString();
    definition += ")";

    this->setDefinition(definition);
}

void Function::composeSource() {
    std::string code = "";
    code += this->getDefinition() + " {\n";
    for (std::string *lineOfCode : this->functionCode->getCode()) {
        code += "    " + *lineOfCode + ";\n";
    }
    code += "}\n";
    this->setSource(code);
}

void Function::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
