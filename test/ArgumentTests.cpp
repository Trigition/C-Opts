#include "../src/Argument.h"
#include "../src/commons/C_Code.h"
#include "catch.hpp"

TEST_CASE("1: Generation of an Argument") {
        char flagChar = 't';
        std::string flagName = "testflag";
        std::string helpDesc = "to help test parsing args";
        std::string manPage = "see Check2 manual for info on testing";
        std::string valueName = "testVal";
        std::string type = "string";
        
        Argument arg(flagChar, flagName, helpDesc, manPage, valueName, type, 1);

        SECTION("Ensure Argument values are properly retained and translated") {
            REQUIRE(arg.get_flag_name() == flagName);
            REQUIRE(arg.get_help_desc() == helpDesc);
            REQUIRE(arg.get_man_page() == manPage);
            REQUIRE(arg.get_value_name() == valueName);
            REQUIRE(arg.get_position() == 1);

            REQUIRE(arg.getType() == TypedInterface::getTypeAlias(type));
        }

}
