#include "C_Code.h"

CodeBlock::CodeBlock() {
    this->depth = 0;
    this->statement_delimiter = "";
}

CodeBlock::~CodeBlock() {
    for (std::string *s : this->code_lines) {
        delete s;
    }
}

void CodeBlock::add_line(std::string &line) {
    this->code_lines.push_back(new std::string(line.c_str()));
}

void CodeBlock::add_line(const char &line) {
    this->code_lines.push_back(new std::string(&line));
}

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
