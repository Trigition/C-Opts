#pragma once

#include "C_Code.h"

// Defines a Code Parameter
class Parameter : public TypedInterface {
    private:
        std::string var_name;
        std::string paramString;

        void setParamString();

    public:
        Parameter(std::string &type, std::string &var_name);
        Parameter(c_str &type, c_str &var_name);
        ~Parameter();

        bool is_same_type(Parameter &compar);
        bool is_same_name(Parameter &compar);

        //Setters
        void set_var_name(std::string &var_name);
        void set_var_name(c_str &var_name);

        // Getters
        std::string& get_var_name() { return this->var_name; };
        std::string& getParamString() { return this->paramString; };
};
