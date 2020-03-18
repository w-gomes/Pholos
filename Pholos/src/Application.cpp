#include "application.hpp"

#include <cassert>

#include "fmt/core.h"

namespace Pholos {

void Application::welcome_message() {
  const std::string logo = fmt::format(
    "\n\tWelcome to Pholos Application!\n"
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

  const std::string commands = fmt::format(
    "- Usage:\n"
    "\t -h \thelp\n"
    "\t -x \texit\n"
    "\t -a \tadd\n"
    "\t -e \tedit\n"
    "\t -d \tdelete\n"
    "\t -s \tsearch\n"
    "\t -q \tquery (more specific)\n"
    "\t -l \tlist all movies or tvshow\n"
    "\t -A \tabout\n");

  const std::string delimiter = fmt::format("\n--------------------------------------------");
  fmt::print("{}{}{}\n", logo, commands, delimiter);
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
