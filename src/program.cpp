#include "program.h"
Program::Program(std::string *new_description, std::string *new_man_page, std::string *new_version) {
    this->description = new std::string(*new_description);
    this->man_page = new std::string(*new_man_page);
    this->version = new std::string(*new_version);
}

Program::~Program() {
    delete this->description;
    delete this->man_page;
    delete this->version;
}

void Program::accept(Visitor *visitor) {

}
