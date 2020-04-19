#pragma once
#include "controller.hpp"
#include "database.hpp"

namespace Pholos {

class Application {
 public:
  inline static Application *instance = nullptr;
  static void welcome_message();

  Application()  = default;
  ~Application() = default;

  Application(const Application &obj) = delete;
  Application &operator=(const Application &obj) = delete;
  Application(Application &&obj)                 = delete;
  Application &operator=(Application &&obj) = delete;

  void run_application();
  void exit_application();
  void init();

 private:
  bool is_running() const;
  bool is_db_loaded() const;

 private:
  bool running_{false};
  bool db_loaded_{false};

  Controller controller_{};
  Database database_{};
};

Application *get_application();
}  // namespace Pholos
