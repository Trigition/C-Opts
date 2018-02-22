/**
 * @file Compiler.cpp
 * @author William Fong
 * @date 2018-02-19
 * @version 0.0.1
 *
 * @brief This file is the source code for the Compiler class
 * @section DESCRIPTION
 * 
 * This source file contains all of the source code implmentation for Compilers.
 */
#include "Compiler.h"

/**
 * @brief This is the main constructor for the Compiler class
 * @param arg_dir The base directory to place source files in
 */
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

/**
 * @brief This is the main constructor for the Compiler class
 * @param arg_dir The base directory to place source files in
 */
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

/**
 * The destructor for Compilers
 */
Compiler::~Compiler() {

}

/**
 * @brief A visitation method for Parameters
 */
void Compiler::dispatch(Parameter *parameter) {

}

/**
 * @brief A visitation method for CodeBlocks
 */
void Compiler::dispatch(CodeBlock *codeblock) {

}

/**
 * @brief A visitation method for Functions
 */
void Compiler::dispatch(Function *function) {
    // Generate header string
    // Generate definition code string
}

/**
 * @brief This function generates a switch parser for Arguments
 * and Actions
 * This function generates a switch statement to determine if a string
 * is specifying an Action or an Argument in the current Action or Program
 * context.
 */
void Compiler::create_switch() {
}

/**
 * @brief This method is called whenever a Compiler instance visits
 * an Action.
 * @param action A reference to the current Action
 * This method is called whenever a Compiler instance visits an Action.
 * Note that the Action may be a subaction and not necessarily a direct
 * main action under a Program.
 */
void Compiler::open_context(Action *action) {

}

/** @brief This method is called whenever a Compiler instance visits
 * a Program
 * @param program A reference to the current Program
 * This method is called whenever a Compiler instance visits a Program.
 * Here is where the appropriate directory structure for the Program's
 * argument parser is generated. Please note that if C-Opts does not have
 * the right Permissions, this step will fail and C-Opts will exit with
 * an error.
 * @TODO Allow C-Opts to have a 'dry run' to see where the directories will
 * be made.
 */
void Compiler::open_context(Program *program) {
    // Construct Program I/O src directory
    std::string command = "mkdir -p " + this->arg_dir;
    int err = system(command.c_str());
    if (err == -1) {
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
    // Create switch for program args and actions
    this->create_switch();
    // Generate parsers for each argument and action
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
