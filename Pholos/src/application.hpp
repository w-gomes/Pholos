#pragma once
#include <filesystem>

#include "controller.hpp"
#include "database.hpp"

namespace Pholos {

namespace fs = std::filesystem;

class Application {
 public:
  static auto welcome_message() -> void;

  // TODO: Find a better way to use Database in Controller...
  Application()
    : controller_(&database_)
    , database_(fs::current_path()) {}
  ~Application() = default;

  // No move or copy
  Application(const Application &obj) = delete;
  Application &operator=(const Application &obj) = delete;
  Application(Application &&obj)                 = delete;
  Application &operator=(Application &&obj) = delete;

  auto run_application() -> void;
  auto exit_application() -> void;
  [[nodiscard]] auto get_database() -> Database &;

 private:
  // methods
  [[nodiscard]] auto is_running() const -> bool;
  [[nodiscard]] auto is_db_loaded() const -> bool;

  // variables
  bool running_{false};
  bool db_loaded_{false};

  Controller controller_;
  Database database_;
};
}  // namespace Pholos
