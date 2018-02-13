#include "Program.h"
Program::Program(std::string &name,
                 std::string &new_description,
                 std::string &new_man_page,
                 std::string &new_version) {
    this->name = name;
    this->description = new_description;
    this->man_page = new_man_page;
    this->version = new_version;
}

Program::Program(c_str &name,
                 c_str &new_description,
                 c_str &new_man_page,
                 c_str &new_version) {
    this->name = name;
    this->description = new_description;
    this->man_page = new_man_page;
    this->version = new_version;
}

Program::~Program() {
    //delete this->description;
    //delete this->man_page;
    //delete this->version;
}

void Program::add_global_arg(Argument &arg) {
    this->global_args.push_back(&arg);
}

void Program::add_action(Action &action) {
    this->actions.push_back(&action);
}

void Program::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
