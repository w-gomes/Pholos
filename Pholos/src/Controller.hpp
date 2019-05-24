#pragma once
#include <string>

namespace Pholos {

class Controller {
   public:
    static Controller *instance;

   private:
};

Controller *getController();
}  // namespace Pholos
