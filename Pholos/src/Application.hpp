#pragma once

#include "Controller.hpp"
#include "Utility.hpp"

namespace Pholos {
class Application {
   public:
    Application();

    static Application *instance;
    ~Application();

    void run();
    bool isRunning();
    void close();

   private:
    bool running_{ false };
    Controller controller_;
    Utility utility_;
};

Application *getApplication();
}  // namespace Pholos
