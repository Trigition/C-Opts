/**
 * @file ArgFile.h
 * @author William Fong
 * @date 2018-05-12
 * @version 0.0.1
 */

#pragma once

#include "C_Code.h"

class ArgFile {
    private:
        std::vector<ArgFile *> dependencies;
        std::vector<Compileable *> content;
        std::string directory;
        std::string name;

        std::ofstream fileout;

        void make_directory();
    public:
        ArgFile(std::string &name, std::string &dir);
        ArgFile(c_str &name, c_str &dir);

        ~ArgFile();

        void write_to_file();
};
