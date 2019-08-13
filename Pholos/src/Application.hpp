#pragma once
#include "Controller/controller.hpp"

namespace Pholos {

class Application {
  public:
    Application();

    static Application *instance;

    ~Application() = default;

    void runApplication();
    bool isRunning() const;
    void exitApplication();
    static void welcomeMessage();

  private:
    bool running_{ false };
    Controller controller_;
};

Application *getApplication();
}  // namespace Pholos
