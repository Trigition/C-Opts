#include "Action.h"

Action::Action(std::string &action_name, std::string &action_desc) {
    this->action_name = action_name;
    this->action_desc = action_desc;
}

Action::~Action() {
    //delete this->action_name;
    //delete this->action_desc;
    for (Argument *a : this->action_arguments) {
        delete a;
    }

    for (Action *a : this->subactions) {
        delete a;
    }
}

void Action::add_argument(Argument &argument) {
    this->action_arguments.push_back(&argument);
}

void Action::add_subaction(Action &subaction) {
    this->subactions.push_back(&subaction);
}

void Action::accept(Visitor &visitor) {
    visitor.dispatch(this);
}
