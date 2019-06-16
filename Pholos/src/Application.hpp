#pragma once
#include "Controller/Controller.hpp"

namespace Pholos {

class Application {
   public:
    Application();

    static Application *instance;
    ~Application() = default;

    void welcomeMessage() const;
    void runApplication();
    bool isRunning() const;
    void exitApplication();

   private:
    bool running_{ false };
    Controller controller_;
};

Application *getApplication();
}  // namespace Pholos
