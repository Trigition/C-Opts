#include "Compiler.h"

Compiler::Compiler(std::string &arg_dir) {
    this->action_context = nullptr;
    this->arg_dir = arg_dir;
#ifdef DEBUG_MODE
    this->debug_mode = false;
#else
    this->debug_mode = true;
#endif
    this->verbose_mode = false;
}

Compiler::Compiler(c_str &arg_dir) {
    this->action_context = nullptr;
    this->arg_dir = arg_dir;
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

void Compiler::open_context(Action *action) {
    
}

void Compiler::open_context(Program *program) {
    // Construct Program I/O src directory
    std::string command = "mkdir -p " + this->arg_dir;
    int err = system(command.c_str());
    if (err == -1) {
        std::cerr << err << '\n';
        std::cerr << "Unable to create parser source directory\nAborting...\n";
        exit(1);
    }
    // Construct arg switch and parse functions for global args
    this->src_file_out.open(this->arg_dir + "/" + program->get_name() + "_args.c");
    this->hdr_file_out.open(this->arg_dir + "/" + program->get_name() + "_args.h");

    // Set program context
    this->program_context = program;
}

void Compiler::dispatch(Program *program) {
    // === Start of new program ===
    this->open_context(program);
    
    for (Argument *arg : program->get_args()) {
        arg->accept(*this);
    }
    for (Action *action : program->get_actions()) {
        // All top program actions get their own namespace
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
