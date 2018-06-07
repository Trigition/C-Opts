#pragma once

#include "C_Code.h"

// Defines a Code Parameter
class Parameter : public TypedInterface {
    private:
        std::string varName;
        std::string paramString;

        void setParamString();

    public:
        Parameter(std::string &type, std::string &varName);
        Parameter(c_str &type, c_str &varName);
        ~Parameter();

        bool isSameType(Parameter &compar);
        bool isSameName(Parameter &compar);

        //Setters
        void setVarName(std::string &varName);
        void setVarName(c_str &varName);

        // Getters
        std::string& getVarName() { return this->varName; };
        std::string& getParamString() { return this->paramString; };
};
