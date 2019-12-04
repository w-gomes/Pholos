#pragma once
#include "controller.hpp"
#include "database.hpp"

namespace Pholos {

class Application {
 public:
  static Application *instance;

  Application();

  Application(const Application &obj) = delete;
  Application &operator=(const Application &obj) = delete;
  Application(Application &&obj)                 = delete;
  Application &operator=(Application &&obj) = delete;

  ~Application() = default;

  void run_application();
  bool is_running() const;
  bool is_db_loaded() const;
  void exit_application();
  static void welcome_message();

 private:
  bool running_{false};
  bool db_loaded_{false};

  Controller controller_{};
  Database database_{};
};

Application *get_application();
}  // namespace Pholos
