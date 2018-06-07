/**
 * @file ArgFile.h
 * @author William Fong
 * @date 2018-05-12
 * @version 0.0.1
 */

#pragma once

#include <fstream>
#include "C_Code.h"

class ArgFile {
    private:
        std::vector<ArgFile *> dependencies;
        std::vector<Defineable *> content;
        std::string directory;
        std::string name;
        std::string localPath;

        void makeDirectory();
    public:
        ArgFile(std::string &name, std::string &dir);
        ArgFile(c_str &name, c_str &dir);

        virtual ~ArgFile() {};

        std::string &getName() { return this->name; };
        std::string &getDirectory() { return this->directory; };
        std::string &getPath() { return this->localPath; };

        std::vector<ArgFile*> &getDependencies() { return this->dependencies; };

        void addDependency(ArgFile *argfile);
        void setLocalPath(const std::string &path) { this->localPath = path; };
        void setLocalPath(c_str &path) { this->localPath = path; };

        virtual void writeToFile() = 0;
};

class HeaderFile : public ArgFile {
    private:
        std::vector<Defineable *> content;
    public:
        HeaderFile(std::string &name, std::string &dir);
        HeaderFile(c_str &name, c_str &dir);
        ~HeaderFile() {};

        void addContent(Defineable *content);
        std::vector<Defineable *> &getContent() { return this->content; };
        virtual void writeToFile();
};

class SourceFile : public ArgFile {
    private:
        std::vector<Compileable *> content;
    public:
        SourceFile(std::string &name, std::string &dir);
        SourceFile(c_str &name, c_str &dir);
        ~SourceFile() {};

        void addContent(Compileable *content);
        std::vector<Compileable *> &getContent() { return this->content; };
        virtual void writeToFile();
};
