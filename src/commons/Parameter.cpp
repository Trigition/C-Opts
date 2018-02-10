#include "C_Code.h"

Parameter::Parameter(std::string &type, std::string &var_name) {
    this->type = type;
    this->var_name = var_name;
}

Parameter::Parameter(c_str &type, c_str &var_name) {
    this->type = type;
    this->var_name = var_name;
}

Parameter::~Parameter() {

}

bool Parameter::is_same_type(Parameter &compar) {
    return this->type == compar.get_type();
}

bool Parameter::is_same_name(Parameter &compar) {
    return this->var_name == compar.get_type();
}

void Parameter::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
