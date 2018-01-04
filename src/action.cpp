#include "action.h"

Action::Action(std::string *action_name, std::string *action_desc) {
    this->action_name = new std::string(*action_name);
    this->action_desc = new std::string(*action_desc);
}

Action::~Action() {
    delete this->action_name;
    delete this->action_desc;
}

void Action::accept(Visitor *visitor) {

}
