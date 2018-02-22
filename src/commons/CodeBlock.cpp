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
#include "C_Code.h"

/**
 * @brief The main constructor for CodeBlocks
 */
CodeBlock::CodeBlock() {
    this->depth = 0;
    this->statement_delimiter = "";
}

/**
 * @brief The main destructor
 * This destructor will also free any code lines associated with it
 */
CodeBlock::~CodeBlock() {
    for (std::string *s : this->code_lines) {
        delete s;
    }
}

/**
 * @brief This method adds a line of code to the CodeBlock
 * @param line A reference to the string representing Code to be
 * inserted.
 */
void CodeBlock::add_line(std::string &line) {
    this->code_lines.push_back(new std::string(line.c_str()));
}

/**
 * @brief This method adds a line of code to the CodeBlock
 * @param line A reference to the string representing Code to be
 * inserted.
 */

void CodeBlock::add_line(c_str &line) {
    this->code_lines.push_back(new std::string(line));
}

/**
 * @brief This method returns all the code lines in the CodeBlock
 * This method will return a single string representing all the code
 * contained within the CodeBlock.
 * TODO Implement formatting
 */
std::string* CodeBlock::get_code() {
    std::string *code = new std::string("");
    *code += "{\n"; //TODO Leave this up to formatting.
    for (std::string *line : this->code_lines) {
        // Indent
        for (uchar j = 0; j < this->depth; j++) {
            *code += "    "; //TODO Leave this up to formatting.
        }
        // Append code
        *code += *line;
        *code += this->statement_delimiter;
    }
    *code += "}"; //TODO Ensure consistency with formatting

    return code;
}

void CodeBlock::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
