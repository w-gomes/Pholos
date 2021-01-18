#pragma once
#include "controller.hpp"
#include "database.hpp"

namespace Pholos {

class Application {
 public:
  static auto welcome_message() -> void;

  Application()  = default;
  ~Application() = default;

  // No move or copy
  Application(const Application &obj) = delete;
  Application &operator=(const Application &obj) = delete;
  Application(Application &&obj)                 = delete;
  Application &operator=(Application &&obj) = delete;

  auto run_application() -> void;
  auto exit_application() -> void;

 private:
  // methods
  [[nodiscard]] auto is_running() const -> bool;
  [[nodiscard]] auto is_db_loaded() const -> bool;

  // variables
  bool running_{false};
  bool db_loaded_{false};

  Controller controller_{};
  Database database_{};
};
}  // namespace Pholos
