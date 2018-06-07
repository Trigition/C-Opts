#include "ArgFile.h"

ArgFile::ArgFile(std::string &name, std::string &dir) {
    this->name = name;

    if (dir.back() != '/') {
        this->directory = dir + '/';
    } else {
        this->directory = dir;
    }

    this->makeDirectory();
    this->localPath = name;
}

ArgFile::ArgFile(c_str &name, c_str &dir) {
    this->name = name;

    if (std::string(dir).back() != '/') {
        this->directory = dir + '/';
    } else {
        this->directory = dir;
    }

    this->makeDirectory();
    this->localPath = name;
}

void ArgFile::makeDirectory() {
    std::string command = "mkdir -p " + this->directory;
    int err = system(command.c_str());
    if (err == -1) {
        std::cerr << "Unable to create directory for file: " << this->name << "\n";
        exit(1);
    }
}

void ArgFile::addDependency(ArgFile *argfile) {
    this->dependencies.push_back(argfile);
}

// HEADER FILES
HeaderFile::HeaderFile(std::string &name, std::string &dir) :
    ArgFile(name, dir) {

    this->setLocalPath(this->getName() + ".h");
}

HeaderFile::HeaderFile(c_str &name, c_str &dir) :
    ArgFile(name, dir) {

    this->setLocalPath(this->getName() + ".h");
}

void HeaderFile::addContent(Defineable *content) {
    this->content.push_back(content);
}

void HeaderFile::writeToFile() {
    std::vector<std::string *> buffer;

    // Open output file
    std::ofstream fileout;
    fileout.open(this->getDirectory() + this->getPath());

    // Add dependencies
    for (ArgFile *f : this->getDependencies()) {
        std::string dep = "#include \"" + f->getPath() + "\"";
        fileout << dep << '\n';
    }

    // Compile definitions
    for (Defineable *d : this->getContent()) {
        buffer.push_back(&d->getDefinition());
    }

    // Flush buffer to file
    for (std::string* definition : buffer) {
        fileout << *definition;
        fileout << ";\n";
    }

    // Cleanup
    fileout.close();
}

// SOURCE FILES
SourceFile::SourceFile(std::string &name, std::string &dir) :
    ArgFile(name, dir) {

    this->setLocalPath(this->getName() + ".c");
}

SourceFile::SourceFile(c_str &name, c_str &dir) :
    ArgFile(name, dir) {

    this->setLocalPath(this->getName() + ".c");
}

void SourceFile::addContent(Compileable *content) {
    this->content.push_back(content);
}

void SourceFile::writeToFile() {
    std::vector<std::string *> buffer;

    // Open output file
    std::ofstream fileout;
    fileout.open(this->getDirectory() + this->getPath());

    // Add dependencies
    for (ArgFile *f : this->getDependencies()) {
        std::string dep = "#include \"" + f->getPath() + "\"";
        fileout << dep << '\n';
    }

    // Compile definitions
    for (Compileable *c : this->getContent()) {
        buffer.push_back(&c->getSource());
    }

    // Flush buffer to file
    for (std::string *source : buffer) {
        fileout << *source;
        fileout << '\n';
    }

    // Cleanup
    fileout.close();
}
