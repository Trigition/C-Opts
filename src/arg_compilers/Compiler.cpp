#include "Compiler.h"
#include "../Argument.h"
#include "../Action.h"
#include "../Program.h"

Compiler::Compiler() {
    this->action_context = nullptr;
#ifdef DEBUG_MODE
    this->debug_mode = false;
#else
    this->debug_mode = true;
#endif
    this->verbose_mode = false;
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
    for (Argument *arg : action->get_arguments()) {
        this->debug_log("Visiting "        +
                        action->get_name() +
                        "'s argument"      +
                        arg->get_flag_name());

        arg->accept(*this);
        // Check to see if there are any name collions
        if (this->current_args[action] == arg->get_flag_name()) {
            // Collision
            std::cerr << "Duplicate flag: " << arg->get_flag_name() << "!\n";
        }
    }

    for (Action *subaction : action->get_subactions()) {
        this->debug_log("Visiting "         +
                        action->get_name()  +
                        "'s subaction: "    +
                        subaction->get_name());
        subaction->accept(*this);
    }
}

void Compiler::dispatch(Argument *argument) {
    this->debug_log("Compiling argument: " + argument->get_flag_name());
}

void Compiler::debug_log(std::string mesg) {
#ifdef DEBUG_MODE
    std::cerr << mesg << "\n";
#endif
}

void Compiler::debug_log(const char * const &mesg) {
#ifdef DEBUG_MODE
    std::cerr << mesg << "\n";
#endif
}
