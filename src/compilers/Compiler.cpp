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
 * @param argDirectory The base directory to place source files in
 */
Compiler::Compiler(std::string &argDirectory) {
    this->actionContext = nullptr;
    this->argDirectory = argDirectory;
#ifdef debugMode
    this->debugMode = false;
#else
    this->debugMode = true;
#endif
    this->verboseMode = false;
}

/**
 * @brief This is the main constructor for the Compiler class
 * @param argDirectory The base directory to place source files in
 */
Compiler::Compiler(c_str &argDirectory) {
    this->actionContext = nullptr;
    this->argDirectory = argDirectory;
#ifdef debugMode
    this->debugMode = false;
#else
    this->debugMode = true;
#endif
    this->verboseMode = false;
}

/**
 * The destructor for Compilers
 */
Compiler::~Compiler() {
    for (ArgFile *argFile : this->files) {
        delete argFile;
    }
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
    // Compile function
    // Place code and declarations into current context
    HeaderFile *headerFile = this->headerMap[this->currentContext];
    SourceFile *sourceFile = this->sourceMap[this->currentContext];

    headerFile->addContent(function);
    sourceFile->addContent(function);
}

/**
 * @brief This function generates a switch parser for Arguments
 * and Actions
 * This function generates a switch statement to determine if a string
 * is specifying an Action or an Argument in the current Action or Program
 * context.
 */
void Compiler::createSwitch(
        std::string &name,
        std::vector<Argument*> &args,
        std::vector<Action*> &actions) {
    //TODO Generate switch statement
    //TODO Arguments are placed before next action
    std::string switchReturnType = "int";
    Function *switcher = new Function(name, switchReturnType);
    switcher->addInputParam(new Parameter("int", "argc"));
    switcher->addInputParam(new Parameter("char **", "arg_str"));

    // Add switch for current action arguments


    switcher->addCodeline("return 0");
}

/**
 * @brief This method is called whenever a Compiler instance visits
 * an Action.
 * @param action A reference to the current Action
 * This method is called whenever a Compiler instance visits an Action.
 * Note that the Action may be a subaction and not necessarily a direct
 * main action under a Program.
 */
void Compiler::openContext(Action *action) {
    // Set context 
    Action *previousAction = this->actionContext;
    this->actionContext = action;
    this->currentContext = action;

    // Initialize source and header files
    std::string headerPath = action->getName();
    std::string sourcePath = action->getName();
    HeaderFile *header = new HeaderFile(headerPath, this->argDirectory);
    SourceFile *source = new SourceFile(sourcePath, this->argDirectory);
    source->addDependency(header);

    // Add dependencies
    if (previousAction != nullptr) {
        this->headerMap[previousAction]->addDependency(header);
    }

    // Add mapping from current action to files
    this->headerMap.insert(headerPair(action, header));
    this->sourceMap.insert(sourcePair(action, source));

    // Add files to list for bookkeeping
    this->files.push_back(header);
    this->files.push_back(source);

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
void Compiler::openContext(Program *program) {
    // Set Context
    this->programContext = program;
    this->currentContext = program;

    // Construct Program I/O src directory
    std::string command = "mkdir -p " + this->argDirectory;
    int err = system(command.c_str());
    if (err == -1) {
        std::cerr << "Unable to create parser source directory\nAborting...\n";
        exit(1);
    }
    // Create files for program context
    std::string headerPath = program->getName();
    std::string sourcePath = program->getName();
    HeaderFile *header = new HeaderFile(headerPath, this->argDirectory);
    SourceFile *source = new SourceFile(sourcePath, this->argDirectory);
    source->addDependency(header);

    // Keep track of files
    this->headerMap.insert(headerPair(program, header));
    this->sourceMap.insert(sourcePair(program, source));

    // Bookkeep files
    this->files.push_back(header);
    this->files.push_back(source);
}

void Compiler::dispatch(Program *program) {
    // === Start of new program ===
    this->openContext(program);

    // Create a struct holding global argument values
    ArgStruct programStruct(program);
    programStruct.accept(*this);

    // Create switch for program args and actions
    // Generate parsers for each argument and action
    for (Argument *arg : program->getArgs()) {
        arg->accept(*this);
    }

    for (Action *action : program->getActions()) {
        // All top program actions get their own namespace
        action->accept(*this);
    }

    // Finish and write to files
    this->writeAllFiles();
}

void Compiler::dispatch(Action *action) {
    // Visiting new action
    this->actionContext = action;
    // Generate Struct holding action argument values
    ArgStruct actionOpts(action);
    actionOpts.accept(*this);

    // Compile opts and subactions
    for (Argument *arg : action->getArguments()) {
        this->debugLog("Visiting "        +
                        action->getName() +
                        "'s argument"      +
                        arg->getFlagName());

        arg->accept(*this);
        // Check to see if there are any name collions
        if (this->currentArgs[action] == arg->getFlagName()) {
            // Collision
            std::cerr << "Duplicate flag: " << arg->getFlagName() << "!\n";
        }
    }

    for (Action *subaction : action->getSubactions()) {
        this->debugLog("Visiting "         +
                        action->getName()  +
                        "'s subaction: "    +
                        subaction->getName());
        subaction->accept(*this);
    }
}

void Compiler::dispatch(Argument *argument) {
    this->debugLog("Compiling argument: " + argument->getFlagName());
    // Compile parser function for argument
    argument->getFunction()->accept(*this);
}

void Compiler::dispatch(ArgStruct *argStruct) {
    HeaderFile *header = this->headerMap[this->currentContext];
    header->addContent(argStruct);
}


void Compiler::writeAllFiles() {
    for (auto const& pair : this->headerMap) {
        pair.second->writeToFile();
    }

    for (auto const& pair : this->sourceMap) {
        pair.second->writeToFile();
    }
}

void Compiler::debugLog(std::string mesg) {
#ifdef debugMode
    std::cerr << mesg << "\n";
#endif
}

void Compiler::debugLog(const char * const &mesg) {
#ifdef debugMode
    std::cerr << mesg << "\n";
#endif
}
