#pragma once

#include <array>
#include <cctype>  // std::tolower()
#include <iostream>
#include <map>
#include <string>
#include <string_view>

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

// The following templates specialization is defined inline,
// otherwise we get error LNK2005
// It needs to be defined as inline or moved into a single cpp file.
// See:
// https://groups.google.com/forum/#!topic/microsoft.public.vc.language/YY47Mc6rC9Y
template <>
inline bool get_user_input<bool>(const std::string &message) {
  fmt::print("{}", message);
  char value;
  std::cin >> value;
  bool result = false;
  if (std::tolower(value) == 'y') {
    result = true;
  }
  return result;
}

template <>
inline std::string get_user_input<std::string>(const std::string &message) {
  fmt::print("{}", message);
  std::string name;
  std::cin.get();  // to consume enter
  std::getline(std::cin, name);
  return name;
}

}  // namespace internal

/*
 * Controller interface
 */
class Controller {
  enum Width : std::size_t {
    Stat          = 13,
    Rating        = 6,
    ID            = 8,
    Episode       = 7,
    Total_Episode = 14
  };

  enum class Command {
    Help   = 0,
    Exit   = 1,
    Add    = 2,
    Edit   = 3,
    Delete = 4,
    Search = 5,
    About  = 6,
    List   = 7
  };

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
  void help();
  void exit();
  void add_menu();
  void edit();
  void edit_menu(char movie_or_tv);
  int get_command(std::string_view command);
  void list_all_movies();
  void list_all_tvshows();
  bool id_exist(const int id, const char obj_type);

 private:
  void add_movie();
  void add_tvshow();

 private:
  static constexpr std::array commands_list = {"HELP",  "EXIT",   "ADD",
                                               "EDIT",  "DELETE", "SEARCH",
                                               "QUERY", "ABOUT",  "LIST"};

  std::map<int, Movies> movies_cache_;
  std::map<int, TvShow> tvshow_cache_;
};

}  // namespace Pholos
