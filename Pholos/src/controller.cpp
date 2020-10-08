#include "controller.hpp"

#include <conio.h>  // _getch()

#include <algorithm>
#include <cassert>  // assert()
#include <cctype>   // std::tolower()
#include <iostream>
#include <iterator>
#include <string>
#include <utility>  // std::pair

#include "application.hpp"
#include "constants.hpp"
#include "database.hpp"
#include "fmt/format.h"
#include "internal.hpp"
#include "movies.hpp"
#include "queries.hpp"
#include "tv-show.hpp"

namespace Pholos {

namespace internal {

// Cannot use a simple overloaded function
// because only return type is different.
template <>
bool get_user_input<bool>(const std::string &message) {
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
std::string get_user_input<std::string>(const std::string &message) {
  fmt::print("{}", message);
  std::string name;
  std::cin.get();  // to consume enter
  std::getline(std::cin, name);
  return name;
}

auto movie_or_tvshow() {
  fmt::print("Movie [m] or Tv Show [t]? : ");
  char user_choose;
  bool user_choice = false;
  Type type;

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

void Controller::press_any_key() {
  fmt::print("\n\nPress any key to continue or [ESC] to leave!");
  int input = _getch();
  if (input == 0x1B)
    this->quit(true);
  else {
    return;
  }
}

// Refactor this
void Controller::draw_menu() {
  fmt::print("\nEnter an option! Type [HELP] for command list : ");
  std::string command;
  std::cin >> command;

  if (auto findResult = std::find(this->commands_list.begin(),
                                  this->commands_list.end(), command);
      findResult == this->commands_list.end()) {
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

Command Controller::get_command(std::string_view command) {
  // Can't use switch with strings
  if (command == "HELP") {
    return Command::Help;
  } else if (command == "EXIT") {
    return Command::Exit;
  } else if (command == "ADD") {
    return Command::Add;
  } else if (command == "EDIT") {
    return Command::Edit;
  } else if (command == "DELETE") {
    return Command::Delete;
  } else if (command == "SEARCH") {
    return Command::Search;
  } else if (command == "ABOUT") {
    return Command::About;
  } else if (command == "LIST") {
    return Command::List;
  } else if (command == "CMD") {
    return Command::Cmd;
  } else {
    return Command::Unknown;
  }
}

inline void Controller::cmd() const {
  fmt::print("Available commands: ");
  std::copy(std::begin(this->commands_list), std::end(this->commands_list),
            std::ostream_iterator<std::string>(std::cout, " "));
  fmt::print("\n");
}

// TODO: incomplete, change the wordings.
inline void Controller::help() const {
  const std::string commands = R"(
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

  )";
  fmt::print(commands);
}

// Add new movie or tvshow
void Controller::add_menu() {
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

void Controller::add_movie() {
  int stat{-1};
  double rating{0.0};

  fmt::print("Adding a new Movie...\nEnter the name, please.\n-> ");
  std::string name;
  std::cin.get();  // to consume enter.
  std::getline(std::cin, name);

  fmt::print("Do you want to add a stat? (y/n) : ");

  char confirm;
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

  Movies movie(internal::add_context<Movies>(name, rating, stat));
  Database::insert(Query::make_insert_query(movie));
  this->load_content();
}

void Controller::add_tvshow() {
  int stat{-1};
  double rating{0.0};
  int episode{0};
  int last_episode{0};

  fmt::print(
    "\n***\nNote: Currently, Pholos doesn't support season. That means if you "
    "want to add a TV Show with many seasons, you have to add a new TV Show "
    "for each "
    "season.\n\nAdding a new TvShow...\nEnter the name, "
    "please.\n-> ");
  std::string name;
  std::cin.get();  // to consume enter.
  std::getline(std::cin, name);

  fmt::print("Do you want to add a stat? (y/n) : ");

  char confirm;
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

  TvShow tvshow(
    internal::add_context<TvShow>(name, stat, rating, episode, last_episode));
  Database::insert(Query::make_insert_query(tvshow));
  this->load_content();
}

// Content cache.
// When we run the application for the first time. We call load_content to
// populate movies_list and tvshow_list. To avoid reading database to check if a
// content is in it.
void Controller::load_content() {
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
             this->movies_cache_.size(), this->tvshow_cache_.size());
#endif
}

void Controller::list_all_movies() {
  const std::string msg =
    "Please enter the search type.\n -1 - all\n 1 - watching\n 2 - plan to "
    "watch\n 3 - completed\n 4 - dropped\n-> ";
  const int search_type = internal::get_user_input<int>(msg);
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
  std::size_t biggest_word = 0;
  std::for_each(movie_list.begin(), movie_list.end(), [&](const auto &obj) {
    std::size_t movie_name_length = obj.second.name().size();
    biggest_word =
      movie_name_length > biggest_word ? movie_name_length : biggest_word;
  });

  // TODO: Turn this into a routine
  // TOP
  fmt::print("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n", Width::ID,
             biggest_word, Width::Rating, Width::Stat, "");
  fmt::print("| {4:<{0}} | {5:<{1}} | {6:<{2}} | {7:<{3}} |\n", Width::ID,
             biggest_word, Width::Rating, Width::Stat, "Movie ID", "Name",
             "Rating", "Stat");

  // MID
  fmt::print("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n", Width::ID,
             biggest_word, Width::Rating, Width::Stat, "");

  std::for_each(movie_list.begin(), movie_list.end(), [=](const auto &obj) {
    fmt::print("| {4:<{0}} | {5:<{1}} | {6:<{2}} | {7:<{3}} |\n", Width::ID,
               biggest_word, Width::Rating, Width::Stat, obj.first,
               obj.second.name(), obj.second.rating(),
               obj.second.stat_as_string());
  });

  // BOTTOM
  fmt::print("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n", Width::ID,
             biggest_word, Width::Rating, Width::Stat, "");
}

void Controller::list_all_tvshows() {
  const std::string msg =
    "Please enter the search type.\n -1 - all\n 1 - watching\n 2 - plan to "
    "watch\n 3 - completed\n 4 - dropped\n-> ";
  const int search_type = internal::get_user_input<int>(msg);
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

  std::size_t biggest_word = 0;
  std::for_each(tvshow_list.begin(), tvshow_list.end(), [&](const auto &obj) {
    std::size_t tv_name_length = obj.second.name().size();
    biggest_word =
      tv_name_length > biggest_word ? tv_name_length : biggest_word;
  });

  // TODO: Turn this into a routine
  // TOP
  fmt::print(
    "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-+"
    "\n",
    Width::ID + 2, biggest_word, Width::Rating, Width::Stat, Width::Episode,
    Width::Total_Episode, "");
  fmt::print(
    "| {6:<{0}} | {7:<{1}} | {8:<{2}} | {9:<{3}} | {10:<{4}} | {11:<{5}} |\n",
    Width::ID + 2, biggest_word, Width::Rating, Width::Stat, Width::Episode,
    Width::Total_Episode, "Tv Show ID", "Name", "Rating", "Stat", "Episode",
    "Total Episodes");

  // MID
  fmt::print(
    "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-+"
    "\n",
    Width::ID + 2, biggest_word, Width::Rating, Width::Stat, Width::Episode,
    Width::Total_Episode, "");

  std::for_each(tvshow_list.begin(), tvshow_list.end(), [=](const auto &obj) {
    fmt::print(
      "| {6:<{0}} | {7:<{1}} | {8:<{2}} | {9:<{3}} | {10:<{4}} | "
      "{11:<{5}} |\n",
      Width::ID + 2, biggest_word, Width::Rating, Width::Stat, Width::Episode,
      Width::Total_Episode, obj.first, obj.second.name(), obj.second.rating(),
      obj.second.stat_as_string(), obj.second.episode(),
      obj.second.last_episode());
  });

  // BOTTOM
  fmt::print(
    "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-+"
    "\n",
    Width::ID + 2, biggest_word, Width::Rating, Width::Stat, Width::Episode,
    Width::Total_Episode, "");
}

bool Controller::id_exist(const int id, Type type) {
  auto found = false;
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

void Controller::edit() {
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

void Controller::edit_menu(Type type) {
  int edit_option = 0;

  fmt::print(
    "\n***\nNote: You must know the object id in other to edit.\nUse list all "
    "to get the id.\n\n");
  // Check for object's id.
  int id     = internal::get_user_input<int>("Please enter the id.\n-> ");
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
      const std::string name = internal::get_user_input<std::string>(
        "Enter the new name, please.\n-> ");
      Database::update_name(id, name, type);
    } break;
    case 2: {
      const int stat = internal::get_user_input<int>(
        "Enter the new stat:\n Watching (1)\n Plan to Watch (2)\n Completed "
        "(3)\n Dropped "
        "(4)\n-> ");
      Database::update_stat(id, stat, type);
    } break;
    case 3: {
      const double rating =
        internal::get_user_input<double>("Enter the new rating.\n-> ");
      Database::update_rating(id, rating, type);
    } break;
    case 4: {
      // We ask user the number of episodes to increment. Default is by 1.
      const bool update_more_than_one = internal::get_user_input<bool>(
        "Do you want to update more than 1? (y/n)\n-> ");
      if (update_more_than_one) {
        const int distance =
          internal::get_user_input<int>("Enter the amount to increment.\n-> ");
        Database::update_episode(id, type, distance);
      } else {
        Database::update_episode(id, type);
      }
    } break;
    case 5: {
      const int total_episode =
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

void Controller::print(const int id, Type type) const {
  std::string top;
  std::string mid;
  std::string title;
  std::string context;
  std::string bottom;
  std::size_t word_size = 0;

  if (type == Type::Movie) {
    const auto movie = movies_cache_.at(id);
    word_size        = movie.name().size();
    top     = fmt::format("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n",
                      Width::ID, word_size, Width::Rating, Width::Stat, "");
    title   = fmt::format("| {4:<{0}} | {5:<{1}} | {6:<{2}} | {7:<{3}} |\n",
                        Width::ID, word_size, Width::Rating, Width::Stat,
                        "Movie ID", "Name", "Rating", "Stat");
    mid     = fmt::format("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n",
                      Width::ID, word_size, Width::Rating, Width::Stat, "");
    context = fmt::format("| {4:<{0}} | {5:<{1}} | {6:<{2}} | {7:<{3}} |\n",
                          Width::ID, word_size, Width::Rating, Width::Stat, id,
                          movie.name(), movie.rating(), movie.stat_as_string());
    bottom  = fmt::format("+-{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}-+\n",
                         Width::ID, word_size, Width::Rating, Width::Stat, "");
  } else if (type == Type::TvShow) {
    const auto tvshow = tvshow_cache_.at(id);
    word_size         = tvshow.name().size();
    top               = fmt::format(
      "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-"
      "+\n",
      Width::ID + 2, word_size, Width::Rating, Width::Stat, Width::Episode,
      Width::Total_Episode, "");
    title = fmt::format(
      "| {6:<{0}} | {7:<{1}} | {8:<{2}} | {9:<{3}} | {10:<{4}} | {11:<{5}} |\n",
      Width::ID + 2, word_size, Width::Rating, Width::Stat, Width::Episode,
      Width::Total_Episode, "Tv Show ID", "Name", "Rating", "Stat", "Episode",
      "Total Episodes");
    mid = fmt::format(
      "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-"
      "+\n",
      Width::ID + 2, word_size, Width::Rating, Width::Stat, Width::Episode,
      Width::Total_Episode, "");
    context = fmt::format(
      "| {6:<{0}} | {7:<{1}} | {8:<{2}} | {9:<{3}} | {10:<{4}} | "
      "{11:<{5}} |\n",
      Width::ID + 2, word_size, Width::Rating, Width::Stat, Width::Episode,
      Width::Total_Episode, id, tvshow.name(), tvshow.rating(),
      tvshow.stat_as_string(), tvshow.episode(), tvshow.last_episode());
    bottom = fmt::format(
      "+-{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}-"
      "+\n",
      Width::ID + 2, word_size, Width::Rating, Width::Stat, Width::Episode,
      Width::Total_Episode, "");
  }

  fmt::print("{}{}{}{}{}", top, title, mid, context, bottom);
}

}  // namespace Pholos
