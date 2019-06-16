#include "Application.hpp"

#include <cassert>

#include "fmt/fmt.hpp"

namespace Pholos {
Application *Application::instance = nullptr;

Application::Application()
    : controller_()
{
    this->instance = this;
}

void Application::welcomeMessage() const
{
    const std::string logo = fmt::format("\n\tWelcome to Pholos Tracker!\n\n\t:::::::::::::::::"
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
                                             "\t-Operations:\n\n"
                                             "\t -h -> help\n"
                                             "\t -x -> exit\n"
                                             "\t -a -> add\n"
                                             "\t -c -> create\n"
                                             "\t -e -> edit\n"
                                             "\t -d -> delete\n"
                                             "\t -s -> search\n"
                                             "\t -q -> query\n");
    fmt::print("{}{}", logo, commands);
}

void Application::runApplication()
{
    this->running_ = true;

    this->welcomeMessage();
    this->controller_.goToMenu();
    while (isRunning()) {
        this->controller_.menu();
    }
}

bool Application::isRunning() const
{
    return this->running_;
}

void Application::exitApplication()
{
    this->running_ = false;
}

Application *getApplication()
{
    assert(Application::instance != nullptr);
    return Application::instance;
}
}  // namespace Pholos
