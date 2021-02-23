#pragma once

#include <array>
#include <map>
#include <string_view>
#include <utility>

#include "constants.hpp"
#include "fmt/format.h"
#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {

/*
 * Controller interface
 */
class Controller {
 public:
  Controller() = default;

  Controller(const Controller &obj) = delete;
  Controller &operator=(const Controller &obj) = delete;
  Controller(Controller &&obj)                 = delete;
  Controller &operator=(Controller &&obj) = delete;

  ~Controller() = default;

  auto load_content() -> void;
  auto press_any_key() -> void;  // This needs a better name
  auto draw_menu() -> void;
  auto cmd() const -> void;
  auto help() const -> void;
  auto add_menu() -> void;
  auto edit() -> void;
  auto edit_menu(Type type) -> void;
  auto get_command(std::string_view command) -> std::pair<Command, Type>;
  auto list_all_movies() -> void;
  auto list_all_tvshows() -> void;
  auto quit(bool quit) -> void { this->quit_ = quit; }
  [[nodiscard]] auto id_exist(int id, Type type) -> bool;
  [[nodiscard]] auto exit() const -> bool { return this->quit_; }

 private:
  // methods
  auto add_movie() -> void;
  auto add_tvshow() -> void;

  auto print(int id, Type type) const -> void;

  // variables
  bool quit_{false};
  inline static std::array<std::string, 10> commands_list = {"HELP",
                                                             "EXIT",
                                                             "ADD",
                                                             "EDIT",
                                                             "DELETE",
                                                             "SEARCH",
                                                             "QUERY",
                                                             "ABOUT",
                                                             "LIST",
                                                             "CMD"};

  std::map<int, Movies> movies_cache_{};
  std::map<int, TvShow> tvshow_cache_{};
};

}  // namespace Pholos
