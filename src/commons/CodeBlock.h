#pragma once

#include "C_Code.h"

class CodeBlock {
    private:
        uchar depth;
        std::vector<std::string *> code_lines;
        std::string statement_delimiter;

    public:
        CodeBlock();
        ~CodeBlock();

        void add_line(std::string &line);
        void add_line(c_str &line);

        // Setters
        void set_depth(uchar depth) { this->depth = depth; };
        void set_statement_delimiter(std::string &delim) {
            this->statement_delimiter = delim;
        };
        void set_statement_delimiter(c_str &delim) {
            this->statement_delimiter = delim;
        }

        // Getters
        uchar get_depth() { return this->depth; };
        std::string get_statement_delimiter() { return this->statement_delimiter; };
        std::vector<std::string *> &getCode() { return this->code_lines; };
        [[deprecated]]
        std::string *get_code();
};
