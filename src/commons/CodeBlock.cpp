#include "c_code.h"

CodeBlock::CodeBlock() {
    this->depth = 0;
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

void CodeBlock::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
