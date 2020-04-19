#include "application.hpp"

#include <cassert>

#include "fmt/core.h"

namespace Pholos {

void Application::welcome_message() {
  const std::string welcome = R"(
      Welcome to Pholos Application!
      Your movie and tv show tracker!

           :::::::::::::::::
           ::::::::::::::::::
           :::::        ::::::
           :::::        ::::::
           :::::        ::::::
           ::::::::::::::::::
           :::::::::::::::::
           :::::
           :::::
           :::::
           :::::
           :::::
           :::::

  )";

  const std::string commands = R"(
  - Usage:

      HELP      help
      EXIT      exit
      ADD       add
      EDIT      edit
      DELETE    delete
      SEARCH    search
      QUERY     query (more specific)
      LIST      list all movies or tvshow
      ABOUT     about

------------------------------------------------
  )";

  fmt::print("{}{}\n", welcome, commands);
}

// Main loop
void Application::run_application() {
  // Welcome message and logo
  Application::welcome_message();

  this->running_ = true;

  // Initializes database
  this->database_.init(this->db_loaded_);

  if (!this->is_db_loaded()) {
    this->running_ = false;
    fmt::print("Existing application! Press any key to leave.");
  }

  // Application loop
  this->controller_.press_any_key();
  while (is_running()) {
    this->controller_.draw_menu();
  }
}

bool Application::is_running() const { return this->running_; }

bool Application::is_db_loaded() const { return this->db_loaded_; }

void Application::exit_application() {
  fmt::print("\nBye!\n");
  this->running_ = false;
}

Application *get_application() {
  assert(Application::instance != nullptr);
  return Application::instance;
}

void Application::init() { this->instance = this; }
}  // namespace Pholos
