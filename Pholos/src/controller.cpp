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
#include "database.hpp"
#include "fmt/core.h"
#include "movies.hpp"
#include "stats.hpp"
#include "tv-show.hpp"

namespace Pholos {

namespace Internal {
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
}  // namespace Internal

void Controller::get_user_response() {
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

  fmt::print("\nEnter an option! Type [-h] for command list : ");
  std::string command;
  std::cin >> command;

  if (auto findResult =
        std::find(this->commands_vector_.begin(), this->commands_vector_.end(), command);
      findResult == this->commands_vector_.end()) {
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
      this->delete_element();
      break;
    case Command::Search:
      // This search if movie exists
      // Unimplemented
      break;
    case Command::Query:
      // This query for specific, i.e., query all movies watching
      // probly hard to implement
      // Unimplemented
      break;
    case Command::About:
      // Show application information
      // Unimplemented
      break;
    case Command::List:
      // List all Elements
      this->list_all();
      break;
  }
}

int Controller::get_command(const std::string &command) {
  int x = -1;
  // Can't use switch with strings
  if (command == "-h") {
    x = 0;
  } else if (command == "-x") {
    x = 1;
  } else if (command == "-a") {
    x = 2;
  } else if (command == "-e") {
    x = 3;
  } else if (command == "-d") {
    x = 4;
  } else if (command == "-s") {
    x = 5;
  } else if (command == "-q") {
    x = 6;
  } else if (command == "-A") {
    x = 7;
  } else if (command == "-l") {
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
  const std::string commands = fmt::format(
    "\n\t - Usage:\n\n"
    "\t -a \tadd.\n"
    "\t\t Add a new object to your track database.\n"
    "\t\t\t User can add movie or tv show.\n"
    "\t\t\t There are two ways to add a new object.\n"
    "\t\t\t Basic: you're asked to enter a name.\n"
    "\t\t\t Full: you're asked to enter name, rating, year, stats(optional).\n\n"
    "\t -e \tedit.\n"
    "\t\t Edit an object.\n\n"
    "\t -d \tdelete.\n"
    "\t\t Delete an object.\n\n"
    "\t -s \tsearch.\n"
    "\t\t Search for an object.\n\n"
    "\t -q \tquery.\n"
    "\t\t Query for an object.\n"
    "\t\t\t Query is an advanced version of search. For instance, user can search "
    "for all movies with status 'Watching'.\n\n"
    "\t -A \tabout.\n"
    "\t\t Information about the application.\n\n"
    "\t -x \texit.\n"
    "\t\t Exit the application.\n\n"
    "\t -h = \thelp.\n"
    "\t\t Show command instructions.\n\n");

  fmt::print(commands);
}

// Add new movie or tvshow
void Controller::add_menu() {
  auto app = get_application();

  fmt::print("Movie [m] or Tv Show [t]?  : ");
  char user_choose;
  bool user_choice = false;

  do {
    std::cin >> user_choose;

    if (std::tolower(user_choose) == 'm') {
      // call movie constructor.
      this->add_movie();
      user_choice = true;
    } else if (std::tolower(user_choose) == 't') {
      // call tvshow constructor.
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
}

void Controller::add_movie() {
  fmt::print(
    "Adding a new Movie...\n"
    "Basic or Complete creation? [b/c] : ");
  char option;
  std::cin >> option;
  std::cin.get();

  auto database = get_database();

  std::string name;
  std::string alias = "";

  if (std::tolower(option) == 'b') {
    fmt::print("----------------------------------------\nEnter the name, please.\n");
    fmt::print("-> ");
    std::getline(std::cin, name);
    fmt::print("Name:> {}\n", name);

    fmt::print(
      "Please add an alias.\nAlias should be lowercase and no spaces."
      "Add underscore instead of spaces\n");
    fmt::print("-> ");
    std::cin >> alias;
    fmt::print("Alias:> {}\n", name);

    fmt::print("You entered:> name = \"{}\", alias = \"{}\".\nDo you Confirm?[y/n]\n-> ", name,
               alias);

    char confirm;
    std::cin >> confirm;

    if (std::tolower(confirm) == 'y') {
      Movies movie(name, alias);
      this->movies_list_.push_back(movie);
      database->save(movie);

      fmt::print("New movie, {}, has been added!\n", name);
    } else if (std::tolower(confirm) == 'n') {
      fmt::print("\nMovie not added. Please run the command again.\n");
    } else {
      fmt::print("\nWrong answer! Please run the command again.\n");
    }

  } else if (std::tolower(option) == 'c') {
    fmt::print("----------------------------------------\nEnter the name, please.\n");

    fmt::print("-> ");
    std::getline(std::cin, name);
    fmt::print("Name:> {}\n", name);

    fmt::print(
      "\nPlease enter the rating, the year and the stats in one single line.\n"
      "Example: 10.0 2009 0\n"
      "Stats: 0 = Plan to Watch, 1 = Watching, 2 = Completed, 3 = Dropped\n");
    double rating;
    int year;
    int stats;

    fmt::print("-> ");
    std::cin >> rating >> year >> stats;
    fmt::print("Rating, Year, Stats:> {} {} {}\n", rating, year, stats);

    fmt::print(
      "Please add an alias.\nAlias should be lowercase and no spaces. "
      "Add underscore instead of spaces\n");
    fmt::print("-> ");
    std::cin >> alias;
    fmt::print("Alias:> {}\n", name);

    fmt::print(
      "You entered:> Name: {0}, Rating: {1}, Year: {2}, Stats: {3}, Alias: {4}."
      "\nDo you confirm?[y/n]\n-> ",
      name, rating, year, stats, alias);

    char confirm;
    std::cin >> confirm;

    if (std::tolower(confirm) == 'y') {
      Movies movie(name, static_cast<double>(rating), static_cast<int>(year),
                   static_cast<Stats>(stats), alias);
      this->movies_list_.push_back(movie);
      database->save(movie);

      fmt::print("New movie, {}, has been added!\n", name);
    } else if (std::tolower(confirm) == 'n') {
      fmt::print("\nMovie not added. Please run the command again.\n");
    } else {
      fmt::print("\nWrong answer! Please run the command again.\n");
    }
  }
}

void Controller::add_tvshow() {
  fmt::print("Adding a new Tv Show...\nBasic or Complete creation? [b/c] : ");
  char option;
  std::cin >> option;
  std::cin.get();

  auto database = get_database();

  std::string name;
  std::string alias = "";

  if (std::tolower(option) == 'b') {
    fmt::print("----------------------------------------\nEnter the name, please.\n");
    fmt::print("-> ");
    std::getline(std::cin, name);
    fmt::print("Name:> {}\n", name);

    fmt::print(
      "Please add an alias.\nAlias should be lowercase and no spaces."
      "Add underscore instead of spaces\n");
    fmt::print("-> ");
    std::cin >> alias;
    fmt::print("Alias:> {}\n", name);

    fmt::print("You entered:> name = \"{}\", alias = \"{}\".\nDo you Confirm?[y/n]\n-> ", name,
               alias);

    char confirm;
    std::cin >> confirm;

    if (std::tolower(confirm) == 'y') {
      TvShow show(name, alias);

      this->tv_show_list_.push_back(show);
      database->save(show);

      fmt::print("New Tv Show, {}, has been added!\n", name);
    } else if (std::tolower(confirm) == 'n') {
      fmt::print("\nTv Show not added. Please run the command again.\n");
    } else {
      fmt::print("\nWrong answer! Please run the command again.\n");
    }

  } else if (std::tolower(option) == 'c') {
    fmt::print("----------------------------------------\nEnter the name, please.\n");

    fmt::print("-> ");
    std::getline(std::cin, name);
    fmt::print("Name:> {}\n", name);

    fmt::print(
      "\nPlease enter the rating, the year, and the stats. in one single line\nExample: "
      "10.0 2008 0\nStats: "
      "0 = Plan to Watch, 1 = Watching, 2 = Completed, 3 = Dropped\n");
    double rating;
    int year;
    int stats;

    fmt::print("-> ");
    std::cin >> rating >> year >> stats;
    fmt::print("Rating, Year, Stats:> {} {} {}\n", rating, year, stats);

    fmt::print(
      "Please add an alias.\nAlias should be lowercase and no spaces. "
      "Add underscore instead of spaces\n");
    fmt::print("-> ");
    std::cin >> alias;
    fmt::print("Alias:> {}\n", name);

    fmt::print(
      "You entered Name: {0}, Rating: {1}, Year: {2}, Stats: {3}, Alias: {4}\nDo you "
      "Confirm?[y/n]\n-> ",
      name, rating, year, stats, alias);

    char confirm;
    std::cin >> confirm;

    if (std::tolower(confirm) == 'y') {
      int season;
      int episode;
      std::map<int, int> seasons;

      fmt::print("Please enter number of seasons\n-> ");
      std::cin >> season;
      fmt::print("Please enter number of episodes for each season\n");
      for (int i = 1; i < season + 1; i++) {
        fmt::print("Season {}\n-> ", i);
        std::cin >> episode;
        fmt::print("Season {0} : Episode(s) {1}\n", i, episode);
        seasons.insert({i, episode});
      }

      fmt::print("You entered:\n");
      for (std::map<int, int>::iterator iterMap = seasons.begin(); iterMap != seasons.end();
           ++iterMap) {
        fmt::print("Seasons {0} : Episode(s) {1}\n", iterMap->first, iterMap->second);
      }

      TvShow show(name, static_cast<int>(year), static_cast<double>(rating), seasons,
                  static_cast<Stats>(stats), alias);
      this->tv_show_list_.push_back(show);
      database->save(show);

      fmt::print("New Tv Show, {}, has been added!\n", name);
    } else if (std::tolower(confirm) == 'n') {
      fmt::print("\nTv Show not added. Please run the command again.\n");
    } else {
      fmt::print("\nWrong answer! Please run the command again.\n");
    }
  }
}

void Controller::delete_element() {
  auto app = get_application();

  fmt::print("Movie [m] or Tv Show [t]?  : ");
  char user_choose;
  bool user_choice = false;

  do {
    std::cin >> user_choose;

    if (std::tolower(user_choose) == 'm') {
      this->delete_movie();
      user_choice = true;
    } else if (std::tolower(user_choose) == 't') {
      this->delete_tvshow();
      user_choice = true;

    } else if (std::tolower(user_choose) == 'c') {
      user_choice = true;
      app->exit_application();
    } else {
      fmt::print("Wrong option! Enter [m] or [t].\n");
      fmt::print("Enter [c] to cancel. : ");
    }
  } while (!user_choice);
}

void Controller::delete_movie() {
  auto database = get_database();
  std::string alias;

  fmt::print(
    "Can only delete by Alias. Enter the movie alias. In lowercase and no spaces. Add "
    "Underscore for spaces.\n-> ");
  std::cin >> alias;

  const bool found = database->is_in_database(alias, 'm');
  if (!found) {
    fmt::print("Movie {} not found", alias);
    return;
  }

  // Maybe a confirmation that the process worked.
  database->delete_element(alias, 'm');
}

void Controller::delete_tvshow() {
  auto database = get_database();
  std::string alias;

  fmt::print("Enter the tvshow alias. In lowercase and no spaces. Add Underscore for spaces.\n-> ");
  std::cin >> alias;

  const bool found = database->is_in_database(alias, 't');
  if (!found) {
    fmt::print("Tv Show {} not found", alias);
    return;
  }

  // Maybe a confirmation that the process worked.
  database->delete_element(alias, 't');
}

// Add better formatting
void Controller::list_all() {
  auto database = get_database();
  char list_what;

  fmt::print("List Movies or TvShow? [m/t] ");
  std::cin >> list_what;

  if (std::tolower(list_what) == 'm') {
    auto uh = database->list_all_movies();
    // @HACK, handle this. std::optinal may not hold a vector.
    std::vector<std::string> message_vector = uh.value();
    Internal::format_objects(message_vector);
  } else if (std::tolower(list_what) == 't') {
    // call list_all_tvshows
  } else {
    // should never happen
  }
}
}  // namespace Pholos
