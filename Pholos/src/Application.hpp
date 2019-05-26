#pragma once

#include "helper/Controller.hpp"
#include "helper/Utility.hpp"
namespace Pholos {
class Application {
   public:
    Application();

    static Application *instance;
    ~Application() = default;

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
