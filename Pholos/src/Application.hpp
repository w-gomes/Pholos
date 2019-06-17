#pragma once
#include <iostream>

#include "Controller/Controller.hpp"

namespace Pholos {

class Application {
   public:
    Application();

    static Application *instance;

    // Debugging
    ~Application()
    {
        std::cout << "\n...Calling Application Destructor...\n";
    }

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
