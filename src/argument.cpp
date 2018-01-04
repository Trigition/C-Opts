#include "argument.h"

Argument::~Argument() {
    delete this->flag_name;
    delete this->help_desc;
    delete this->man_page;
    delete this->value_name;
    delete this->type;
}

void Argument::accept(Visitor *visitor) {

}
