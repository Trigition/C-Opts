#include "ArgStruct.h"

ArgStruct::ArgStruct(Action *action) {
    this->load_arguments(action->get_arguments());
    this->name = action->get_name();
}

ArgStruct::ArgStruct(Program *program) {
    this->load_arguments(program->get_args());
    this->name = program->get_name();
}

ArgStruct::~ArgStruct() {
    
}

void ArgStruct::load_arguments(std::vector<Argument *>& args) {
    for (Argument *arg : args) {
        this->add_argument(arg);
    }
}

void ArgStruct::add_argument(Argument *arg) {
    this->arguments.push_back(arg);
}

void ArgStruct::accept(Visitor &visitor) {
    visitor.dispatch(this);
}

void ArgStruct::composeDefinition() {
    std::string definition = "typedef struct {\n";
    for (Argument *arg : this->arguments) {
        arg->composeDefinition();
        definition += "\t" + arg->getDefinition() + ";\n";
    }

    definition += "} " + this->name + "_opts;";
    this->setDefinition(definition);
}
