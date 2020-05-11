#pragma once

#include <array>
#include <map>
#include <string>
#include <string_view>

#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {

class Controller {
  enum Width : std::size_t { Stat = 13, Rating = 6, ID = 8, Episode = 7, Total_Episode = 14 };

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
  static constexpr std::array commands_list = {"HELP",   "EXIT",  "ADD",   "EDIT", "DELETE",
                                               "SEARCH", "QUERY", "ABOUT", "LIST"};

  std::map<int, Movies> movies_cache_;
  std::map<int, TvShow> tvshow_cache_;
};

namespace internal {

template <typename T>
T get_user_input(const std::string &message) {
  fmt::print("{}", message);
  T id;
  std::cin >> id;
  return id;
}
}  // namespace internal
}  // namespace Pholos
