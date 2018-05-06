#pragma once

#include "C_Code.h"

// Defines a Code Parameter
class Parameter : public Compileable {
    private:
        std::string type;
        std::string var_name;

    public:
        Parameter(std::string &type, std::string &var_name);
        Parameter(c_str &type, c_str &var_name);
        ~Parameter();

        bool is_same_type(Parameter &compar);
        bool is_same_name(Parameter &compar);

        //Setters
        void set_type(std::string &type) { this->type = type; };
        void set_type(c_str &type) { this->type = type; };

        void set_var_name(std::string &var_name) { this->var_name = var_name; };
        void set_var_name(c_str &var_name) { this->var_name = var_name; };

        // Getters
        std::string& get_type() { return this->type; };
        std::string& get_var_name() { return this->var_name; };
        std::string get_definition() { return this->get_type() + this->get_var_name(); };

        void accept(Visitor &visitor);
};
