#include "ArgFile.h"

ArgFile::ArgFile(std::string &name, std::string &dir) {
    this->name = name;
    this->directory = dir;

    this->make_directory();
}

ArgFile::ArgFile(c_str &name, c_str &dir) {
    this->name = name;
    this->directory = directory;
    this->make_directory();
}

void ArgFile::make_directory() {
    std::string command = "mkdir -p " + this->directory;
    int err = system(command.c_str());
    if (err == -1) {
        std::cerr << "Unable to create directory for file: " << this->name << "\n";
        exit(1);
    }
}

ArgFile::~ArgFile() {

}

void ArgFile::write_to_file() {
    std::string path = this->directory + this->path;
    this->fileout.open(path);
}
