#include "../src/Program.h"
#include "../src/Argument.h"
#include "../src/Action.h"
#include "catch.hpp"

TEST_CASE("1: Generation of a program") {
    std::string programName = "Test Program";
    std::string programDesc = "A test program for Catch2";
    std::string programMan = "See Catch2 man page for information";
    std::string version = "0.0.1";
    Program testProgram(programName, programDesc, programMan, version);

    REQUIRE(&testProgram != nullptr);

    SECTION("Ensure program values are properly retained") {
        REQUIRE( testProgram.getName() == programName);
        REQUIRE( testProgram.getDescription() == programDesc);
        REQUIRE( testProgram.getManPage() == programMan);
        REQUIRE( testProgram.getVersion() == version);
    }

    SECTION("Allow addition of Arguments to Program") {
        char flagChar = 't';
        std::string flagName = "testflag";
        std::string helpDesc = "to help test parsing args";
        std::string manPage = "see Check2 manual for info on testing";
        std::string valueName = "testVal";
        std::string type = "string";
        
        Argument arg(flagChar, flagName, helpDesc, manPage, valueName, type, 1);
        testProgram.addGlobalArg(arg);
        REQUIRE(testProgram.getArgs().size() == 1);
    
    }
 
    SECTION("Allow addition of Actions to Program") {
        std::string name = "SubTest";
        std::string desc = "This action is testing if an action can be added";
        Action action(name, desc);
        testProgram.addAction(action);
    }
}
