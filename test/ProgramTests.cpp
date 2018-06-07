#include "../src/Program.h"
#include "../src/Argument.h"
#include "../src/Action.h"
#include "catch.hpp"

TEST_CASE("1: Generation of a program") {
    std::string program_name = "Test Program";
    std::string program_desc = "A test program for Catch2";
    std::string program_man = "See Catch2 man page for information";
    std::string version = "0.0.1";
    Program testProgram(program_name, program_desc, program_man, version);

    REQUIRE(&testProgram != nullptr);

    SECTION("Ensure program values are properly retained") {
        REQUIRE( testProgram.get_name() == program_name);
        REQUIRE( testProgram.get_description() == program_desc);
        REQUIRE( testProgram.get_man_page() == program_man);
        REQUIRE( testProgram.get_version() == version);
    }

    SECTION("Allow addition of Arguments to Program") {
        char flagChar = 't';
        std::string flagName = "testflag";
        std::string helpDesc = "to help test parsing args";
        std::string manPage = "see Check2 manual for info on testing";
        std::string valueName = "testVal";
        std::string type = "string";
        
        Argument arg(flagChar, flagName, helpDesc, manPage, valueName, type, 1);
        testProgram.add_global_arg(arg);
        REQUIRE(testProgram.get_args().size() == 1);
    
    }
 
    SECTION("Allow addition of Actions to Program") {
        std::string name = "SubTest";
        std::string desc = "This action is testing if an action can be added";
        Action action(name, desc);
        testProgram.add_action(action);
    }
}
