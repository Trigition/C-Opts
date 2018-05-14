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
void Compiler::create_switch(
        std::string &name,
        std::vector<Argument*> &args,
        std::vector<Action*> &actions) {
    //TODO Generate switch statement
    //TODO Arguments are placed before next action
    std::string switch_return_type = "int";
    Function *switcher = new Function(name, switch_return_type);
    switcher->add_input_param(new Parameter("int", "argc"));
    switcher->add_input_param(new Parameter("char **", "arg_str"));

    // Add switch for current action arguments


    switcher->add_codeline("return 0");
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
    // Close current contexts
    this->src_file_out.close();
    this->hdr_file_out.close();
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

    // Have source file include its header file
    std::string *header_dep = new std::string("#include \"" + program->get_name() + "_args.h" + "\"\n");
    this->source_buffer.push_back(header_dep);

    // Set program context
    this->program_context = program;
}

void Compiler::dispatch(Program *program) {
    // === Start of new program ===
    this->open_context(program);

    // Create a struct holding global argument values
    ArgStruct program_struct(program);
    program_struct.accept(*this);
    // Create switch for program args and actions
    // this->create_switch();
    // Generate parsers for each argument and action
    for (Argument *arg : program->get_args()) {
        arg->accept(*this);
    }

    // Before entering action namespaces. Flush all 
    // header and source to file.
    this->flush_header();
    this->flush_source();
    for (Action *action : program->get_actions()) {
        // All top program actions get their own namespace
        action->accept(*this);
    }
}

void Compiler::dispatch(Action *action) {
    // Visiting new action
    this->action_context = action;
    // Generate Struct holding action argument values
    ArgStruct action_opts(action);
    action_opts.accept(*this);

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

void Compiler::dispatch(ArgStruct *arg_struct) {
    std::string *opt_struct = arg_struct->create_typedef();
    this->debug_log(*opt_struct);
    this->header_buffer.push_back(opt_struct);
}

void Compiler::flush_header() {
    for (std::string *str : this->header_buffer) {
        this->hdr_file_out << *str;
    }
    this->header_buffer.clear();
}

void Compiler::flush_source() {
    for (std::string *str : this->source_buffer) {
      this->src_file_out << *str;
    }
    this->source_buffer.clear();
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
