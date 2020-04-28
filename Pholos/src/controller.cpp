#include "controller.hpp"

#include <conio.h>  // _getch()

#include <algorithm>
#include <cassert>
#include <cctype>  // std::tolower()
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "application.hpp"
#include "common.hpp"
#include "database.hpp"
#include "fmt/core.h"
#include "movies.hpp"
#include "stats.hpp"
#include "tv-show.hpp"

namespace Pholos {

/*
namespace Internal {
// @Incomplete implementation of formatting output
void format_objects(const std::vector<std::string> &message) {
  // the size of the header and footer should be the size of the longest string
  const int header_and_footer_size = 100;
  // @Incomplete
  const std::string header = fmt::format("{:#^{}}\n", " List of Movies ", header_and_footer_size);
  fmt::print(header);
  for (const auto &msg : message) {
    fmt::print(msg);
  }
  const std::string footer = fmt::format("{:#^{}}", "", header_and_footer_size);
  fmt::print(footer);
}
}  // namespace Pholos
*/

void Controller::press_any_key() {
  auto app = get_application();

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
      // Unimplemented
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

  Movies movie(common::add_context<Movies>(name, rating, stat));
  auto database = get_database();
  this->movies_list_.push_back(movie);
  database->save(movie);
}

void Controller::add_tvshow() {
  int stat{-1};
  double rating{0.0};
  int episode{0};
  int last_episode{0};

  fmt::print("Adding a new TvShow...\nEnter the name, please.\n-> ");
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

  TvShow tvshow(common::add_context<TvShow>(name, stat, rating, episode, last_episode));
}

// Make this Generic, works for movies and tvshows.
void Controller::list_all() {
  auto database = get_database();
  char list_what;

  fmt::print("List Movies or TvShow? [m/t] ");
  std::cin >> list_what;

  if (std::tolower(list_what) == 'm') {
    std::vector<std::string> message_vector = database->list_all_movies();
    // This should be a
    std::for_each(message_vector.begin(), message_vector.end(),
                  [](std::string_view s) { fmt::print(s); });
  } else if (std::tolower(list_what) == 't') {
    // call list_all_tvshows
  } else {
    // should never happen
  }
}
}  // namespace Pholos
