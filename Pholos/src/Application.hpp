#pragma once
#include "Controller/controller.hpp"
#include "Helper/database.hpp"

namespace Pholos {

class Application {
  public:
    static Application *instance;

    Application();

    Application(const Application &obj) = delete;
    Application &operator=(const Application &obj) = delete;
    Application(Application &&obj)                 = delete;
    Application &operator=(Application &&obj) = delete;

    ~Application() = default;

    void runApplication();
    bool isRunning() const;
    void exitApplication();
    static void welcomeMessage();

  private:
    bool running_{ false };
    Controller controller_{};
    Database database_{};
};

Application *getApplication();
}  // namespace Pholos
