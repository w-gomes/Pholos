#include "Application.hpp"

#include <cassert>

namespace Pholos {
Application *Application::instance = nullptr;

Application::Application()
{
    this->instance = this;
}

Application::~Application()
{
}

void Application::run()
{
    this->running_ = true;
    while (isRunning()) {
        this->utility_.usage();
    }
}

bool Application::isRunning()
{
    return this->running_;
}

void Application::close()
{
    this->running_ = false;
}

Application *getApplication()
{
    assert(Application::instance != nullptr);
    return Application::instance;
}
}  // namespace Pholos
