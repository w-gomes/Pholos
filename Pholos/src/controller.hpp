#pragma once

#include <array>
#include <cctype>  // std::tolower()
#include <iostream>
#include <map>
#include <string>
#include <string_view>

#include "constants.hpp"
#include "fmt/core.h"
#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {

namespace internal {

// Helper to get user input such as id, rating, episodes, etc.
template <typename T>
T get_user_input(const std::string &message) {
  fmt::print("{}", message);
  T value;
  std::cin >> value;
  return value;
}

// Template specialization declaration
template <>
bool get_user_input<bool>(const std::string &message);

template <>
std::string get_user_input<std::string>(const std::string &message);

}  // namespace internal

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

  void load_content();
  void press_any_key();  // This needs a better name
  void draw_menu();
  void cmd() const;
  void help() const;
  void add_menu();
  void edit();
  void edit_menu(Type type);
  Command get_command(std::string_view command);
  void list_all_movies();
  void list_all_tvshows();
  bool id_exist(const int id, Type type);
  bool quit(bool quit) { return this->quit_ = quit; }
  bool exit() { return this->quit_; }

 private:
  // methods
  void add_movie();
  void add_tvshow();

  void print(const int id, Type type) const;

  // variables
  bool quit_{false};
  static constexpr std::array commands_list = {
    "HELP",   "EXIT",  "ADD",   "EDIT", "DELETE",
    "SEARCH", "QUERY", "ABOUT", "LIST", "CMD"};

  std::map<int, Movies> movies_cache_{};
  std::map<int, TvShow> tvshow_cache_{};
};

}  // namespace Pholos
