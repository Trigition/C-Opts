#pragma once

#include "C_Code.h"

class CodeBlock {
    private:
        uchar depth;
        std::vector<std::string *> codeLines;
        std::string statementDelimiter;

    public:
        CodeBlock();
        ~CodeBlock();

        void addLine(std::string &line);
        void addLine(c_str &line);

        // Setters
        void setDepth(uchar depth) { this->depth = depth; };
        void setStatementDelimiter(std::string &delim) {
            this->statementDelimiter = delim;
        };
        void set_statementDelimiter(c_str &delim) {
            this->statementDelimiter = delim;
        }

        // Getters
        uchar getDepth() { return this->depth; };
        std::string getStatementDelimiter() { return this->statementDelimiter; };
        std::vector<std::string *> &getCode() { return this->codeLines; };
};
