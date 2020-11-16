#pragma once
#include "controller.hpp"
#include "database.hpp"

namespace Pholos {

class Application {
 public:
  static void welcome_message();

  Application()  = default;
  ~Application() = default;

  // No move or copy
  Application(const Application &obj) = delete;
  Application &operator=(const Application &obj) = delete;
  Application(Application &&obj)                 = delete;
  Application &operator=(Application &&obj) = delete;

  void run_application();
  void exit_application();

 private:
  // methods
  [[nodiscard]] bool is_running() const;
  [[nodiscard]] bool is_db_loaded() const;

  // variables
  bool running_{false};
  bool db_loaded_{false};

  Controller controller_{};
  Database database_{};
};
}  // namespace Pholos
