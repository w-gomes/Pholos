#include "controller.hpp"

#include <conio.h>  // _getch()

#include <algorithm>
#include <cassert>   // assert()
#include <cctype>    // std::tolower()
#include <iostream>  // std::cin, std::getline
#include <iterator>
#include <string>
#include <string_view>
#include <utility>  // std::pair

#include "application.hpp"
#include "constants.hpp"
#include "database.hpp"
#include "fmt/format.h"
#include "internal.hpp"
#include "movies.hpp"
#include "numeric-aliases.hpp"  // rust-like aliases
#include "queries.hpp"
#include "tv-show.hpp"
#include "utility.hpp"

namespace Pholos {

namespace internal {

auto movie_or_tvshow() {
  fmt::print("Movie [m] or Tv Show [t]? : ");
  auto user_choose = tl::uchar{};
  auto type        = Type{};
  auto user_choice{false};

  do {
    std::cin >> user_choose;

    if (std::tolower(user_choose) == 'm') {
      user_choice = true;
      type        = Type::Movie;
    } else if (std::tolower(user_choose) == 't') {
      user_choice = true;
      type        = Type::TvShow;
    } else if (std::tolower(user_choose) == 'c') {
      user_choice = true;
      type        = Type::None;
      break;
    } else {
      fmt::print("Wrong option! Enter [m] or [t].\n");
      fmt::print("Enter [c] to cancel. : ");
    }
  } while (!user_choice);
  std::cin.clear();

  return std::make_pair(user_choice, type);
}

}  // namespace internal

auto Controller::press_any_key() -> void {
  fmt::print("\n\nPress any key to continue or [ESC] to leave!");
  auto input = _getch();
  enum esc {
    key_esc = 0x1B,
  };

  if (input == esc::key_esc) {
    this->quit(true);
  } else {
    return;
  }
}

// Refactor this
auto Controller::draw_menu() -> void {
  fmt::print("\nEnter an option! Type [HELP] for command list : ");
  auto command = std::string{};
  std::cin >> command;

  if (auto findResult = std::find(Controller::commands_list.begin(),
                                  Controller::commands_list.end(),
                                  command);
      findResult == Controller::commands_list.end()) {
    fmt::print("Command not found!\n");
    return;
  }

  switch (this->get_command(command)) {
    case Command::Help:
      this->help();
      break;
    case Command::Exit:
      this->quit(true);
      break;
    case Command::Add:
      // Add new movie or tv show
      this->add_menu();
      break;
    case Command::Edit:
      // Edit existing object
      // User can change:
      //  Movie and TvShow
      // - name
      // - stat
      // - rating
      //
      //  TvShow
      // - episode
      // - last_episode
      //
      this->edit();
      break;
    case Command::Delete:
      // Delete a movie or a tvshow
      // Unimplemented
      fmt::print("{}", "\nDelete command...\n");
      break;
    case Command::Search:
      // This search if movie exists
      // Unimplemented
      fmt::print("{}", "\nSearch command...\n");
      break;
    case Command::About:
      // Show application information
      // Unimplemented
      fmt::print("{}", "\nAbout command...\n");
      break;
    case Command::List:
      // List all Elements
      // TODO: Add options to list only movies and tvshows,
      // and by filters (e.g. list all completed).
      this->list_all_movies();
      this->list_all_tvshows();
      break;
    case Command::Cmd:
      // Show all list of commands.
      // Unimplemented
      this->cmd();
      break;
    case Command::Unknown:
      fmt::print("Unknown command!\n");
      break;
  }
}

auto Controller::get_command(std::string_view command) -> Command {
  auto cmd = Command{};
  // Can't use switch with strings
  if (command == "HELP") {
    cmd = Command::Help;
  } else if (command == "EXIT") {
    cmd = Command::Exit;
  } else if (command == "ADD") {
    cmd = Command::Add;
  } else if (command == "EDIT") {
    cmd = Command::Edit;
  } else if (command == "DELETE") {
    cmd = Command::Delete;
  } else if (command == "SEARCH") {
    cmd = Command::Search;
  } else if (command == "ABOUT") {
    cmd = Command::About;
  } else if (command == "LIST") {
    cmd = Command::List;
  } else if (command == "CMD") {
    cmd = Command::Cmd;
  } else {
    cmd = Command::Unknown;
  }

  return cmd;
}

inline auto Controller::cmd() const -> void {
  fmt::print("Available commands: ");
  std::copy(std::begin(Controller::commands_list),
            std::end(Controller::commands_list),
            std::ostream_iterator<std::string>(std::cout, " "));
  fmt::print("\n");
}

// TODO: incomplete, change the wordings.
inline auto Controller::help() const -> void {
  auto commands = std::string_view{R"(
    - Usage:

        ADD     add
                Add a new movie or tv show to your database.
                Options: m -> movie
                         t -> tv show

                You can add a name, a status (Watching, Plan to Watch, Completed or Dropped) [optional],
                and a rating [optional] to a Movie and Tv Show.

                Additionally, for Tv Show, you can add a number of episodes and the episode you're on.

        EDIT    edit
                Edit an object.
                Options: m -> movie
                         t -> tv show

                Users must know the id of the movie or tvshow.
                Picking the option 'm' or 't', a table will be displayed, so that users can get the id.
                For movies, users can edit the name, status and rating.
                For tvshows, users can edit the name, status, rating, total episodes and the current episode.

        DELETE  delete
                Delete an object.

        SEARCH  search
                Search for an object.

        LIST    list
                List all
                List all movies or tv show.
                List by filters (e.g. list completed movies or/and tv show)

                Options: m -> movie
                         t -> tv show

                Inner Options: -1 -> list all
                                1 -> list only watching
                                2 -> list only plan to watch
                                3 -> list only completed
                                4 -> list only dropped

        EXIT    exit
                Exit the application.

        CMD     command
                Show available commands.

        ABOUT   about
                Information about the application.

        HELP    help
                Show this command list.

  )"};
  fmt::print(commands);
}

// Add new movie or tvshow
auto Controller::add_menu() -> void {
  auto [user_chose, type] = internal::movie_or_tvshow();

  if (user_chose) {
    switch (type) {
      case Type::Movie:
        this->add_movie();
        break;
      case Type::TvShow:
        this->add_tvshow();
        break;
      case Type::None:
        return;
    }
  }
}

auto Controller::add_movie() -> void {
  auto stat{0};
  auto rating{0.0};

  fmt::print("Adding a new Movie...\nEnter the name, please.\n-> ");
  auto name = std::string{};
  std::cin.get();  // to consume enter.
  std::getline(std::cin, name);

  fmt::print("Do you want to add a stat? (y/n) : ");

  auto confirm = tl::uchar{};
  std::cin >> confirm;
  if (std::tolower(confirm) == 'y') {
    fmt::print(
      "Enter the stat.\n Watching (1)\n Plan to Watch (2)\n Completed (3)\n "
      "Dropped (4)\n-> ");
    std::cin >> stat;
  }

  fmt::print("Do you want to add a rating? (y/n) : ");
  std::cin >> confirm;
  if (std::tolower(confirm) == 'y') {
    fmt::print("Enter the rating.\n-> ");
    std::cin >> rating;
  }

  auto movie = Movies(name, rating, stat);
  Database::insert(Query::make_insert_query(movie));
  this->load_content();
}

auto Controller::add_tvshow() -> void {
  auto stat{0};
  auto rating{0.0};
  auto episode{0};
  auto last_episode{0};

  fmt::print(
    "\n***\nNote: Currently, Pholos doesn't support season. That means if you "
    "want to add a TV Show with many seasons, you have to add a new TV Show "
    "for each "
    "season.\n\nAdding a new TvShow...\nEnter the name, "
    "please.\n-> ");
  auto name = std::string{};
  std::cin.get();  // to consume enter.
  std::getline(std::cin, name);

  fmt::print("Do you want to add a stat? (y/n) : ");

  auto confirm = tl::uchar{};
  std::cin >> confirm;
  if (std::tolower(confirm) == 'y') {
    fmt::print(
      "Enter the stat.\n Watching (1)\n Plan to Watch (2)\n Completed (3)\n "
      "Dropped (4)\n-> ");
    std::cin >> stat;
  }

  fmt::print("Do you want to add a rating? (y/n) : ");
  std::cin >> confirm;
  if (std::tolower(confirm) == 'y') {
    fmt::print("Enter the rating.\n-> ");
    std::cin >> rating;
  }

  fmt::print("Do you want to add how many episodes there are? (y/n) : ");
  std::cin >> confirm;
  if (std::tolower(confirm) == 'y') {
    fmt::print("Enter the total episodes.\n-> ");
    std::cin >> last_episode;

    if (stat != 3) {
      fmt::print("What episode are you on?\n-> ");
      std::cin >> episode;
    }
  }

  auto tvshow = TvShow(name, rating, stat, episode, last_episode);
  Database::insert(Query::make_insert_query(tvshow));
  this->load_content();
}

// Content cache.
// When we run the application for the first time. We call load_content to
// populate movies_list and tvshow_list. To avoid reading database to check if a
// content is in it.
auto Controller::load_content() -> void {
#if defined(_DEBUG)
  fmt::print("Loading contents into cache...\n");
#endif
  // Desired API call
  // database.select(Type::Movie, Select_Type::All);
  const auto movies_list = Database::select_movies();
  // Desired API call
  // database.select(Type::TvShow, Select_Type::All);
  const auto tvshows_list = Database::select_tvshows();

  // Whenever we add a new object, we call load_content to reload the cache...
  // So that we can get the object's id.
  // So we clear the cache before loading it again.
  // There is probably a better way, but we're doing this for now.
  this->movies_cache_.clear();
  this->tvshow_cache_.clear();

  this->movies_cache_ = movies_list;
  this->tvshow_cache_ = tvshows_list;

#if defined(_DEBUG)
  fmt::print("Loaded movies and tvshows cache... {} movies, {} tvshow.\n",
             this->movies_cache_.size(),
             this->tvshow_cache_.size());
#endif
}

auto Controller::list_all_movies() -> void {
  auto msg = std::string_view{
    "Please enter the search type.\n 0 - all\n 1 - watching\n 2 - plan to "
    "watch\n 3 - completed\n 4 - dropped\n-> "};
  const auto search_type = internal::get_user_input<int>(msg);
  fmt::print("search_type is {}.\n", search_type);

  const auto movie_list =
    Database::select_movies(static_cast<Stats>(search_type));
  if (movie_list.empty()) {
    fmt::print("\n***\nNo movie was found for this search type.\n");
    return;
  }

  // Get the length of the biggest movie's name.
  // id width | word width | rating width | stat width |
  // 0          1            2              3
  // Id | Name | Rating | Stat
  // 4    5      6        7
  const auto biggest_word =
    (*std::ranges::max_element(movie_list,
                               [](const auto &obj1, const auto &obj2) {
                                 return obj1.second.name().size() <
                                        obj2.second.name().size();
                               }))
      .second.name()
      .size();

  // TODO: Turn this into a routine
  // TOP
  fmt::print("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n",
             Width::ID,
             biggest_word,
             Width::Rating,
             Width::Stat,
             "");
  fmt::print("| {4:<{0}} | {5:<{1}} | {6:<{2}} | {7:<{3}} |\n",
             Width::ID,
             biggest_word,
             Width::Rating,
             Width::Stat,
             "Movie ID",
             "Name",
             "Rating",
             "Stat");

  // MID
  fmt::print("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n",
             Width::ID,
             biggest_word,
             Width::Rating,
             Width::Stat,
             "");

  std::for_each(movie_list.begin(), movie_list.end(), [=](const auto &obj) {
    fmt::print("| {4:<{0}} | {5:<{1}} | {6:<{2}} | {7:<{3}} |\n",
               Width::ID,
               biggest_word,
               Width::Rating,
               Width::Stat,
               obj.first,
               obj.second.name(),
               obj.second.rating(),
               obj.second.stat_as_string());
  });

  // BOTTOM
  fmt::print("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n",
             Width::ID,
             biggest_word,
             Width::Rating,
             Width::Stat,
             "");
}

auto Controller::list_all_tvshows() -> void {
  auto msg = std::string_view{
    "Please enter the search type.\n 0 - all\n 1 - watching\n 2 - plan to "
    "watch\n 3 - completed\n 4 - dropped\n-> "};
  const auto search_type = internal::get_user_input<int>(msg);
  fmt::print("search_type is {}.\n", search_type);

  const auto tvshow_list =
    Database::select_tvshows(static_cast<Stats>(search_type));
  if (tvshow_list.empty()) {
    fmt::print("\n***\nNo tvshow was found for this search type.\n");
    return;
  }

  // id width | word width | rating width | stat width | episode width |
  // 0          1            2              3            4
  // total episode
  // 5
  //
  // Id | Name | Rating | Stat | Episode | Total Episodes
  // 6    7      8        9      10        11
  const auto biggest_word =
    (*std::ranges::max_element(tvshow_list,
                               [](const auto &obj1, const auto &obj2) {
                                 return obj1.second.name().size() <
                                        obj2.second.name().size();
                               }))
      .second.name()
      .size();

  // TODO: Turn this into a routine
  // TOP
  fmt::print(
    "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-+"
    "\n",
    Width::ID + 2,
    biggest_word,
    Width::Rating,
    Width::Stat,
    Width::Episode,
    Width::Total_Episode,
    "");
  fmt::print(
    "| {6:<{0}} | {7:<{1}} | {8:<{2}} | {9:<{3}} | {10:<{4}} | {11:<{5}} |\n",
    Width::ID + 2,
    biggest_word,
    Width::Rating,
    Width::Stat,
    Width::Episode,
    Width::Total_Episode,
    "Tv Show ID",
    "Name",
    "Rating",
    "Stat",
    "Episode",
    "Total Episodes");

  // MID
  fmt::print(
    "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-+"
    "\n",
    Width::ID + 2,
    biggest_word,
    Width::Rating,
    Width::Stat,
    Width::Episode,
    Width::Total_Episode,
    "");

  std::for_each(tvshow_list.begin(), tvshow_list.end(), [=](const auto &obj) {
    fmt::print(
      "| {6:<{0}} | {7:<{1}} | {8:<{2}} | {9:<{3}} | {10:<{4}} | "
      "{11:<{5}} |\n",
      Width::ID + 2,
      biggest_word,
      Width::Rating,
      Width::Stat,
      Width::Episode,
      Width::Total_Episode,
      obj.first,
      obj.second.name(),
      obj.second.rating(),
      obj.second.stat_as_string(),
      obj.second.episode(),
      obj.second.last_episode());
  });

  // BOTTOM
  fmt::print(
    "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-+"
    "\n",
    Width::ID + 2,
    biggest_word,
    Width::Rating,
    Width::Stat,
    Width::Episode,
    Width::Total_Episode,
    "");
}

auto Controller::id_exist(int id, Type type) -> bool {
  auto found{false};
  switch (type) {
    case Type::Movie:
      if (auto search = this->movies_cache_.find(id);
          search != this->movies_cache_.end()) {
        found = true;
      }
      break;
    case Type::TvShow:
      if (auto search = this->tvshow_cache_.find(id);
          search != this->tvshow_cache_.end()) {
        found = true;
        break;
      }
    case Type::None:
      fmt::print("Error! case Type::None is not a real object!\n");
      break;
  }
  return found;
}

auto Controller::edit() -> void {
  // Which object we want to edit: movie or tv show.
  const auto [user_chose, type] = internal::movie_or_tvshow();

  if (user_chose) {
    switch (type) {
      case Type::Movie:
        this->list_all_movies();
        break;
      case Type::TvShow:
        this->list_all_tvshows();
        break;
      case Type::None:
        return;
    }
  }
  this->edit_menu(type);
}

auto Controller::edit_menu(Type type) -> void {
  auto edit_option{0};

  fmt::print(
    "\n***\nNote: You must know the object id in other to edit.\nUse list all "
    "to get the id.\n\n");
  // Check for object's id.
  auto id    = internal::get_user_input<int>("Please enter the id.\n-> ");
  bool exist = this->id_exist(id, type);

  if (!exist) {
    fmt::print("The id doesn't exist.\n");
    return;
  }

  // TODO: handle wrong usage: edit_option > 5 and < 1;
  switch (type) {
    case Type::Movie:
      fmt::print(
        "Edit options:\n Change name (1)\n Change stat (2)\n Change rating "
        "(3)\n\n-> ");
      std::cin >> edit_option;
      break;
    case Type::TvShow:
      fmt::print(
        "Edit options:\n Change name (1)\n Change stat (2)\n Change rating "
        "(3)\n "
        "Change episode "
        "(4)\n "
        "Change total episode (5)\n\n-> ");
      std::cin >> edit_option;
      break;
    case Type::None:
      break;
  }

  // TODO: handle wrong user input
  // We update the objects in database using the ID.
  switch (edit_option) {
    case 1: {
      const auto name = internal::get_user_input<std::string>(
        "Enter the new name, please.\n-> ");
      Database::update_name(id, name, type);
    } break;
    case 2: {
      const auto stat = internal::get_user_input<int>(
        "Enter the new stat:\n Watching (1)\n Plan to Watch (2)\n Completed "
        "(3)\n Dropped "
        "(4)\n-> ");
      Database::update_stat(id, stat, type);
    } break;
    case 3: {
      const auto rating =
        internal::get_user_input<double>("Enter the new rating.\n-> ");
      Database::update_rating(id, rating, type);
    } break;
    case 4: {
      // We ask user the number of episodes to increment. Default is by 1.
      const auto update_more_than_one = internal::get_user_input<bool>(
        "Do you want to update more than 1? (y/n)\n-> ");
      if (update_more_than_one) {
        const auto distance =
          internal::get_user_input<int>("Enter the amount to increment.\n-> ");
        Database::update_episode(id, type, distance);
      } else {
        Database::update_episode(id, type);
      }
    } break;
    case 5: {
      const auto total_episode =
        internal::get_user_input<int>("Enter the new total episode.\n-> ");
      Database::update_total_episode(id, total_episode, type);
    } break;
    default:
      fmt::print("Unhandled case!!!\n");
      break;
  }
  // LOL: We have to update the cache.
  this->load_content();

  this->print(id, type);
}

auto Controller::print(int id, Type type) const -> void {
  auto top       = std::string{};
  auto mid       = std::string{};
  auto title     = std::string{};
  auto context   = std::string{};
  auto bottom    = std::string{};
  auto word_size = std::size_t{0};

  if (type == Type::Movie) {
    const auto movie = movies_cache_.at(id);
    word_size        = movie.name().size();
    top     = fmt::format("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n",
                      Width::ID,
                      word_size,
                      Width::Rating,
                      Width::Stat,
                      "");
    title   = fmt::format("| {4:<{0}} | {5:<{1}} | {6:<{2}} | {7:<{3}} |\n",
                        Width::ID,
                        word_size,
                        Width::Rating,
                        Width::Stat,
                        "Movie ID",
                        "Name",
                        "Rating",
                        "Stat");
    mid     = fmt::format("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n",
                      Width::ID,
                      word_size,
                      Width::Rating,
                      Width::Stat,
                      "");
    context = fmt::format("| {4:<{0}} | {5:<{1}} | {6:<{2}} | {7:<{3}} |\n",
                          Width::ID,
                          word_size,
                          Width::Rating,
                          Width::Stat,
                          id,
                          movie.name(),
                          movie.rating(),
                          movie.stat_as_string());
    bottom  = fmt::format("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n",
                         Width::ID,
                         word_size,
                         Width::Rating,
                         Width::Stat,
                         "");
  } else if (type == Type::TvShow) {
    const auto tvshow = tvshow_cache_.at(id);
    word_size         = tvshow.name().size();
    top               = fmt::format(
      "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-"
      "+\n",
      Width::ID + 2,
      word_size,
      Width::Rating,
      Width::Stat,
      Width::Episode,
      Width::Total_Episode,
      "");
    title = fmt::format(
      "| {6:<{0}} | {7:<{1}} | {8:<{2}} | {9:<{3}} | {10:<{4}} | {11:<{5}} |\n",
      Width::ID + 2,
      word_size,
      Width::Rating,
      Width::Stat,
      Width::Episode,
      Width::Total_Episode,
      "Tv Show ID",
      "Name",
      "Rating",
      "Stat",
      "Episode",
      "Total Episodes");
    mid = fmt::format(
      "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-"
      "+\n",
      Width::ID + 2,
      word_size,
      Width::Rating,
      Width::Stat,
      Width::Episode,
      Width::Total_Episode,
      "");
    context = fmt::format(
      "| {6:<{0}} | {7:<{1}} | {8:<{2}} | {9:<{3}} | {10:<{4}} | "
      "{11:<{5}} |\n",
      Width::ID + 2,
      word_size,
      Width::Rating,
      Width::Stat,
      Width::Episode,
      Width::Total_Episode,
      id,
      tvshow.name(),
      tvshow.rating(),
      tvshow.stat_as_string(),
      tvshow.episode(),
      tvshow.last_episode());
    bottom = fmt::format(
      "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-"
      "+\n",
      Width::ID + 2,
      word_size,
      Width::Rating,
      Width::Stat,
      Width::Episode,
      Width::Total_Episode,
      "");
  }

  fmt::print("{}{}{}{}{}", top, title, mid, context, bottom);
}

}  // namespace Pholos
