#pragma once

#include <array>
#include <map>
#include <string>
#include <string_view>

#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {

class Controller {
  // Plan to watch has 13 characters.
  constexpr static std::size_t stat_width          = 13;
  constexpr static std::size_t rating_width        = 6;
  constexpr static std::size_t id_width            = 8;
  constexpr static std::size_t episode_width       = 7;
  constexpr static std::size_t total_episode_width = 14;

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
  int get_command(std::string_view command);
  void list_all_movies();
  void list_all_tvshows();

 private:
  void add_movie();
  void add_tvshow();

 private:
  Command commands_{};
  static constexpr std::array commands_list = {"HELP",   "EXIT",  "ADD",   "EDIT", "DELETE",
                                               "SEARCH", "QUERY", "ABOUT", "LIST"};

  std::map<int, Movies> movies_cache_;
  std::map<int, TvShow> tvshow_cache_;
};
}  // namespace Pholos
