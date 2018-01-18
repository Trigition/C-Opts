#include "Compiler.h"
#include "../Argument.h"
#include "../Action.h"
#include "../Program.h"

Compiler::Compiler() {

}

Compiler::~Compiler() {

}

void Compiler::dispatch(Parameter *parameter) {

}

void Compiler::dispatch(CodeBlock *codeblock) {

}

void Compiler::dispatch(Function *function) {
    // Generate header string
    // Generate definition code string
}

void Compiler::dispatch(Program *program) {
    // Start of new program, construct source files in
    // separate directories
    for (Argument *arg : program->get_global_args()) {
        arg->accept(*this);
    }
    for (Action *action : program->get_actions()) {
        action->accept(*this);
    }
}

void Compiler::dispatch(Action *action) {
    // Visiting new action
    this->action_context = action;
    // Compile opts and subactions
    for (Argument *arg : action->action_arguments) {
        arg->accept(*this);
    }
    for (Action *subaction : action->subactions) {
        subaction->accept(*this);
    }

void Compiler::dispatch(Argument *argument) {

}
