#include "Application.hpp"
#include "fmt/fmt.hpp"

#include <cassert>

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
                                             "\t -h or --help\n"
                                             "\t -x or --exit\n"
                                             "\t -c or --create\n\n\n"
                                             "\t -a or --add \n"
                                             "\t -e or --edit \n"
                                             "\t -d or --delete \n"
                                             "\t -s or --search \n"
                                             "\t -q or --query \n");
    fmt::print("{}{}", logo, commands);
}

void Application::runApplication()
{
    this->running_ = true;

    this->welcomeMessage();
    this->controller_.proceedToMenu();
    while (isRunning()) {
        this->controller_.menu();
    }
}

bool Application::isRunning()
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
