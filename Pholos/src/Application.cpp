#include "application.hpp"

#include <cassert>

#include "fmt/core.h"

namespace Pholos {
Application *Application::instance = nullptr;

Application::Application()
{
    this->instance = this;
}

void Application::welcome_message()
{
    const std::string logo = fmt::format("\n\tWelcome to Pholos Application!\n"
                                         "\tYour movie and tv show tracker!\n"
                                         "\n\t:::::::::::::::::"
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
    fmt::print("{}{}\n", logo, commands);
}

// Main loop
void Application::run_application()
{
    this->running_ = true;

    // Application loop
    Application::welcome_message();
    this->controller_.get_user_response();
    while (is_running()) {
        this->controller_.draw_menu();
    }
}

bool Application::is_running() const
{
    return this->running_;
}

void Application::exit_application()
{
    fmt::print("\nBye!\n");
    this->running_ = false;
}

Application *get_application()
{
    assert(Application::instance != nullptr);
    return Application::instance;
}
}  // namespace Pholos
