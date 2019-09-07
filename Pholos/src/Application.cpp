#include "application.hpp"

#include <cassert>

#include "fmt/fmt.hpp"

namespace Pholos {
Application *Application::instance = nullptr;

Application::Application()
{
    this->instance = this;
}

void Application::welcomeMessage()
{
    const std::string logo =
        fmt::format("\n\tWelcome to Pholos Tracker!\n\n\t:::::::::::::::::"
                    "\n\t::::::::::::::::::"
                    "\n\t:::::        ::::::"
                    "\n\t:::::        ::::::"
                    "\n\t:::::        ::::::"
                    "\n\t::::::::::::::::::"
                    "\n\t:::::::::::::::::"
                    "\n\t:::::"
                    "\n\t:::::"
                    "\n\t:::::"
                    "\n\t:::::"
                    "\n\t:::::"
                    "\n\t:::::\n\n");

    const std::string commands = fmt::format("- Usage:\n"
                                             "\t -h \thelp\n"
                                             "\t -x \texit\n"
                                             "\t -a \tadd\n"
                                             "\t -e \tedit\n"
                                             "\t -d \tdelete\n"
                                             "\t -s \tsearch\n"
                                             "\t -q \tquery (advanced searching.)\n"
                                             "\t -A \tabout\n");
    fmt::print("{}{}\n\n", logo, commands);
}

// Main loop
void Application::runApplication()
{
    this->running_ = true;

    // Application loop
    Application::welcomeMessage();
    this->controller_.getUserResponse();
    while (isRunning()) {
        this->controller_.drawMenu();
    }
}

bool Application::isRunning() const
{
    return this->running_;
}

void Application::exitApplication()
{
    fmt::print("\nExiting application!\n");
    this->running_ = false;
}

Application *getApplication()
{
    assert(Application::instance != nullptr);
    return Application::instance;
}
}  // namespace Pholos
