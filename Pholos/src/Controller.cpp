#include "Controller.hpp"

#include <cassert>
#include <iostream>

namespace Pholos {

Controller *Controller::instance = nullptr;

Controller *getController()
{
    assert(Controller::instance != nullptr);

    return Controller::instance;
}
}  // namespace Pholos
