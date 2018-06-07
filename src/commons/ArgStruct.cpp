#include "ArgStruct.h"

ArgStruct::ArgStruct(Action *action) {
    this->loadArguments(action->getArguments());
    this->name = action->getName();
}

ArgStruct::ArgStruct(Program *program) {
    this->loadArguments(program->getArgs());
    this->name = program->getName();
}

ArgStruct::~ArgStruct() {
    
}

void ArgStruct::loadArguments(std::vector<Argument *>& args) {
    for (Argument *arg : args) {
        this->addArgument(arg);
    }
}

void ArgStruct::addArgument(Argument *arg) {
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

    definition += "} " + this->name + "_opts";
    this->setDefinition(definition);
}
