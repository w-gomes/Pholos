#pragma once
#include "Controller/controller.hpp"

namespace Pholos {

class Application {
  public:
    Application();

    static Application *instance;

    // Debugging
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
