#include "application.hpp"

#include <cassert>  // assert()
#include <string_view>

#include "fmt/format.h"

namespace Pholos {

void Application::welcome_message() {
  std::string_view welcome = R"(
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

  std::string_view commands = R"(
  - Usage:

      ADD       add
      EDIT      edit
      DELETE    delete
      SEARCH    search
      LIST      list all movies or tvshow
      EXIT      exit
      CMD       list of commands
      ABOUT     about
      HELP      help

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

  // Database is loaded, so we can load the contents into the cache.
  this->controller_.load_content();

  // Application loop
  this->controller_.press_any_key();
  while (is_running()) {
    if (this->controller_.exit()) {
      // pepegawildhammer
      this->exit_application();
      break;
    }
    this->controller_.draw_menu();
  }
}

bool Application::is_running() const { return this->running_; }

bool Application::is_db_loaded() const { return this->db_loaded_; }

void Application::exit_application() {
  fmt::print("\nBye!\n");
  this->running_ = false;
}
}  // namespace Pholos
