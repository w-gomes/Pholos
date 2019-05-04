#include "Controller.hpp"

#include <cassert>
#include <iostream>

namespace Pholos {

Controller *Controller::instance = nullptr;

Controller::Controller()
{
    this->instance = this;
}

void Controller::addMovie()
{
}

Controller *getController()
{
    assert(Controller::instance != nullptr);

    return Controller::instance;
}
}  // namespace Pholos
