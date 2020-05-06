#include "controller.hpp"

#include <conio.h>  // _getch()

#include <algorithm>
#include <cassert>  // assert()
#include <cctype>   // std::tolower()
#include <iostream>
#include <string>

#include "application.hpp"
#include "database.hpp"
#include "fmt/core.h"
#include "internal.hpp"
#include "movies.hpp"
#include "stats.hpp"
#include "tv-show.hpp"

namespace Pholos {

void Controller::press_any_key() {
  auto *app = get_application();

  fmt::print("\n\nPress any key to continue or [ESC] to leave!");
  int input = _getch();
  if (input == 0x1B)
    app->exit_application();
  else {
    return;
  }
}

// Refactor this
void Controller::draw_menu() {
  // Maybe we don't need this.
  // auto app = get_application();

  fmt::print("\nEnter an option! Type [HELP] for command list : ");
  std::string command;
  std::cin >> command;

  if (auto findResult = std::find(this->commands_list.begin(), this->commands_list.end(), command);
      findResult == this->commands_list.end()) {
    fmt::print("Command not found!\n");
    return;
  }

  int y = this->get_command(command);
  assert(y != -1);
  switch (static_cast<Command>(y)) {
    case Command::Help:
      this->help();
      break;
    case Command::Exit:
      this->exit();
      break;
    case Command::Add:
      // Add new movie or tv show
      this->add_menu();
      break;
    case Command::Edit:
      // Edit existing object
      // Unimplemented
      break;
    case Command::Delete:
      // Delete a movie or a tvshow
      // Unimplemented
    case Command::Search:
      // This search if movie exists
      // Unimplemented
      break;
    case Command::Query:
      // This query is more complete. You can query for specific things.
      // Like, list all movies tagged as watching.
      // Unimplemented
      break;
    case Command::About:
      // Show application information
      // Unimplemented
      break;
    case Command::List:
      // List all Elements
      this->list_all_movies();
      this->list_all_tvshows();
      break;
  }
}

int Controller::get_command(std::string_view command) {
  int x = -1;
  // Can't use switch with strings
  if (command == "HELP") {
    x = 0;
  } else if (command == "EXIT") {
    x = 1;
  } else if (command == "ADD") {
    x = 2;
  } else if (command == "EDIT") {
    x = 3;
  } else if (command == "DELETE") {
    x = 4;
  } else if (command == "SEARCH") {
    x = 5;
  } else if (command == "QUERY") {
    x = 6;
  } else if (command == "ABOUT") {
    x = 7;
  } else if (command == "LIST") {
    x = 8;
  }

  return x;
}

void Controller::exit() {
  auto app = get_application();
  app->exit_application();
}

// TODO: incomplete, change the wordings.
void Controller::help() {
  const std::string commands = R"(
    - Usage:

        ADD     add
                Add a new object to your track database.
                User can add movie or tv show.
                There two ways to add a new object.
                Basic: you're asked to enter a name.
                Full: you're asked to enter name, rating, year, stats(optional).

        EDIT    edit
                Edit an object.

        DELETE  delete
                Delete an object.

        SEARCH  search
                Search for an object.

        QUERY   query
                Search for objects.
                Search for objects with specific parameters.
                E.g. search movies whose status is watching.

        LIST    list
                List all movies or tv show.

        ABOUT   about
                Information about the application.

        EXIT    exit
                Exit the application.

        HELP    help
                Show this command list.


  )";
  fmt::print(commands);
}

// Add new movie or tvshow
void Controller::add_menu() {
  auto app = get_application();

  fmt::print("Movie [m] or Tv Show [t]? : ");
  char user_choose;
  bool user_choice = false;

  do {
    std::cin >> user_choose;

    if (std::tolower(user_choose) == 'm') {
      this->add_movie();
      user_choice = true;
    } else if (std::tolower(user_choose) == 't') {
      this->add_tvshow();
      user_choice = true;

    } else if (std::tolower(user_choose) == 'c') {
      user_choice = true;
      app->exit_application();
    } else {
      fmt::print("Wrong option! Enter [m] or [t].\n");
      fmt::print("Enter [c] to cancel. : ");
    }
  } while (!user_choice);
  std::cin.clear();
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
    fmt::print("Enter the stat.\nWatching (1), Plan to Watch (2), Completed (3), Dropped (4)\n-> ");
    std::cin >> stat;
  }

  fmt::print("Do you want to add a rating? (y/n) : ");
  std::cin >> confirm;
  if (std::tolower(confirm) == 'y') {
    fmt::print("Enter the rating.\n-> ");
    std::cin >> rating;
  }

  Movies movie(internal::add_context<Movies>(name, rating, stat));
  auto *database = get_database();
  this->add(movie);
  database->save(movie);
}

void Controller::add_tvshow() {
  int stat{-1};
  double rating{0.0};
  int episode{0};
  int last_episode{0};

  fmt::print(
    "Note: Currently, Pholos doesn't support season. That means if you "
    "want to add a TV Show with many seasons, you have to add a new TV Show for each "
    "season.\n\nAdding a new TvShow...\nEnter the name, "
    "please.\n-> ");
  std::string name;
  std::cin.get();  // to consume enter.
  std::getline(std::cin, name);

  fmt::print("Do you want to add a stat? (y/n) : ");

  char confirm;
  std::cin >> confirm;
  if (std::tolower(confirm) == 'y') {
    fmt::print("Enter the stat.\nWatching (1), Plan to Watch (2), Completed (3), Dropped (4)\n-> ");
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

  TvShow tvshow(internal::add_context<TvShow>(name, stat, rating, episode, last_episode));
  auto *database = get_database();
  this->add(tvshow);
  database->save(tvshow);
}

void Controller::add(const Movies &movie) { this->movies_list_.push_back(movie); }

void Controller::add(const TvShow &tv) { this->tv_show_list_.push_back(tv); }

// Content cache.
// When we run the application for the first time. We call load_content to
// populate movies_list and tvshow_list. To avoid reading database to check if a content
// is in it.
void Controller::load_content() {
#if defined(_DEBUG)
  fmt::print("Loading contents into cache...\n");
#endif
  auto *database    = get_database();
  auto movies_list  = database->select_all_movies();
  auto tvshows_list = database->select_all_tvshows();

  this->movies_list_  = movies_list;
  this->tv_show_list_ = tvshows_list;

#if defined(_DEBUG)
  fmt::print("Loaded movies and tvshows cache... movie: {}s, tvshows {}s",
             this->movies_list_.size(), this->tv_show_list_.size());
#endif
}

void Controller::list_all_movies() {
  fmt::print("\n");
  if (this->movies_list_.empty()) {
    fmt::print("Your movie list is empty!\n");
    return;
  }

  std::size_t biggest_word = 0;
  std::for_each(this->movies_list_.begin(), this->movies_list_.end(), [&](const Movies &movie) {
    std::size_t movie_name_length = movie.name().size();
    biggest_word = movie_name_length > biggest_word ? movie_name_length : biggest_word;
  });

  fmt::print("{1:<{0}} | {2:<{0}} | {3:<{0}}\n", biggest_word, "Name", "Rating", "Stat");
  std::for_each(this->movies_list_.begin(), this->movies_list_.end(), [=](const Movies &movie) {
    fmt::print("{1:<{0}} | {2:<{0}} | {3:<{0}}\n", biggest_word, movie.name(), movie.rating(),
               movie.stat_to_string());
  });
}

void Controller::list_all_tvshows() {
  fmt::print("\n");
  if (this->tv_show_list_.empty()) {
    fmt::print("Your tv show list is empty!\n");
    return;
  }

  std::size_t biggest_word = 0;
  std::for_each(this->tv_show_list_.begin(), this->tv_show_list_.end(), [&](const TvShow &tv) {
    std::size_t tv_name_length = tv.name().size();
    biggest_word               = tv_name_length > biggest_word ? tv_name_length : biggest_word;
  });
  fmt::print("{1:<{0}} | {2:<{0}} | {3:<{0}} | {4:<{0}} | {5:<{0}}\n", biggest_word, "Name",
             "Rating", "Stat", "Episode", "Total Episodes");
  std::for_each(this->tv_show_list_.begin(), this->tv_show_list_.end(), [=](const TvShow &tv) {
    fmt::print("{1:<{0}} | {2:<{0}} | {3:<{0}} | {4:<{0}} | {5:<{0}}\n", biggest_word, tv.name(),
               tv.rating(), tv.stat_to_string(), tv.episode(), tv.last_episode());
  });
}
}  // namespace Pholos
