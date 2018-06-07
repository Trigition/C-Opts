/**
 * @file CodeBlock.cpp
 * @author William Fong
 * @date 2018-02-18
 * @version 0.0.1
 *
 * @brief This is the source code for the class CodeBlock
 * @section DESCRIPTION
 *
 * This source file contains all of the code implementation for CodeBlocks
 */
#include "CodeBlock.h"

/**
 * @brief The main constructor for CodeBlocks
 */
CodeBlock::CodeBlock() {
    this->depth = 0;
    this->statementDelimiter = "";
}

/**
 * @brief The main destructor
 * This destructor will also free any code lines associated with it
 */
CodeBlock::~CodeBlock() {
    for (std::string *s : this->codeLines) {
        delete s;
    }
}

/**
 * @brief This method adds a line of code to the CodeBlock
 * @param line A reference to the string representing Code to be
 * inserted.
 */
void CodeBlock::addLine(std::string &line) {
    this->codeLines.push_back(new std::string(line.c_str()));
}

/**
 * @brief This method adds a line of code to the CodeBlock
 * @param line A reference to the string representing Code to be
 * inserted.
 */

void CodeBlock::addLine(c_str &line) {
    this->codeLines.push_back(new std::string(line));
}
