#include "controller.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>   // std::tolower()
#include <conio.h>  // _getch()
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "application.hpp"
#include "database.hpp"
#include "fmt/core.h"
#include "movies.hpp"
#include "stats.hpp"

namespace Pholos {

void Controller::get_user_response()
{
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
void Controller::draw_menu()
{
  // Maybe we don't need this.
  // auto app = get_application();

  fmt::print("\nEnter an option! Type [-h] for command list : ");
  std::string command;
  std::cin >> command;

  auto findResult =
    std::find(this->commands_vector_.begin(), this->commands_vector_.end(), command);

  if (findResult == this->commands_vector_.end()) {
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
  }
}

int Controller::get_command(const std::string &command)
{
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
  }

  return x;
}

void Controller::exit()
{
  auto app = get_application();
  app->exit_application();
}

// TODO: incomplete, change the wordings.
void Controller::help()
{
  const std::string commands =
    fmt::format("\n\t - Usage:\n\n"
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
void Controller::add_menu()
{
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

void Controller::add_movie()
{
  fmt::print("Adding a new Movie...\n"
             "Basic or Complete creation? [b/c] : ");
  char option_creation;
  std::cin >> option_creation;
  std::cin.get();

  auto database = get_database();

  std::string name;
  double rating;
  int year;
  int stats;
  char confirm;

  if (std::tolower(option_creation) == 'b') {
    fmt::print("\nPlease enter a name\nPlease add no spaces, use underscore\n");
    do {
      fmt::print("-> ");
      std::cin >> name;
      fmt::print("You entered \"{}\"\nDo you Confirm?[y/n]\n-> ", name);
      std::cin >> confirm;
      if (std::tolower(confirm) == 'y') {
        break;
      }
    } while (true);

    Movies movie(name);
    this->movies_list_.push_back(movie);
    database->save(movie);

  } else if (std::tolower(option_creation) == 'c') {
    fmt::print("\nPlease enter the name, the rating, the year and the stats. in one "
               "single line\nExample: "
               "The_Avengers 10.0 2009 0\n.Use underscore instead of spaces.\nStats: "
               "0 = Plan to Watch, 1 = Watching, 2 = Completed, 3 = Dropped\n");
    do {
      fmt::print("-> ");
      std::cin >> name >> rating >> year >> stats;
      fmt::print("You entered Name: {0}, Rating: {1}, Year: {2}, Stats: {3}.\nDo you "
                 "Confirm?[y/n]\n-> ",
                 name, rating, year, stats);
      std::cin >> confirm;
      if (std::tolower(confirm) == 'y') {
        break;
      }
    } while (true);

    Movies movie(name, static_cast<double>(rating), static_cast<int>(year),
                 static_cast<Stats>(stats));
    this->movies_list_.push_back(movie);
    database->save(movie);
  }

  fmt::print("New movie, {}, has been added!\n", name);
}

void Controller::add_tvshow()
{
  fmt::print("Adding a new Tv Show...\nBasic or Complete creation? [b/c] : ");
  char option_creation;
  std::cin >> option_creation;
  std::cin.get();

  auto database = get_database();

  std::string name;
  double rating;
  int year;
  int stats;
  int season;
  int episode;
  char confirm;
  std::map<int, int> seasons;

  if (std::tolower(option_creation) == 'b') {
    fmt::print("Please enter a name\nPlease add no spaces, use underscore\n");
    do {
      fmt::print("-> ");
      std::cin >> name;
      fmt::print("You entered \"{}\"\nDo you Confirm?[y/n]\n-> ", name);
      std::cin >> confirm;
      if (std::tolower(confirm) == 'y') {
        break;
      }
    } while (true);

    TvShow show(name);

    this->tv_show_list_.push_back(show);
    database->save(show);

  } else if (std::tolower(option_creation) == 'c') {
    fmt::print("Please enter a name, rating, year, and stats. in one single line\nExample: "
               "Two_and_a_half_man 10.0 2008 0\n.Use underscore instead of spaces.\nStats: "
               "0 = Plan to Watch, 1 = Watching, 2 = Completed, 3 = Dropped\n");
    do {
      fmt::print("-> ");
      std::cin >> name >> rating >> year >> stats;
      fmt::print("You entered Name: {0}, Rating: {1}, Year: {2}, Stats: {3}.\nDo you "
                 "Confirm?[y/n]\n-> ",
                 name, rating, year, stats);
      std::cin >> confirm;
      if (std::tolower(confirm) == 'y') {
        break;
      }
    } while (true);

    fmt::print("Please enter number of seasons\n-> ");
    std::cin >> season;
    fmt::print("Please enter number of episodes for each season\n");
    for (int i = 1; i < season + 1; i++) {
      fmt::print("Season {}\n-> ", i);
      std::cin >> episode;
      fmt::print("Season {0} : Episode(s) {1}\n", i, episode);
      seasons.insert({ i, episode });
    }

    fmt::print("You entered:\n");
    for (std::map<int, int>::iterator iterMap = seasons.begin(); iterMap != seasons.end();
         ++iterMap) {
      fmt::print("Seasons {0} : Episode(s) {1}\n", iterMap->first, iterMap->second);
    }

    TvShow show(name, static_cast<int>(year), static_cast<double>(rating), seasons,
                static_cast<Stats>(stats));
    this->tv_show_list_.push_back(show);
    database->save(show);
  }

  fmt::print("New Tv Show, {}, has been added!\n", name);
}

void Controller::delete_element()
{
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

void Controller::delete_movie()
{
  auto database = get_database();
  fmt::print("Enter the movie name. If name has spaces add _ (underscore)\n: ");
  std::string name;
  std::cin >> name;

  const bool found = database->search(name, 'm');
  if (!found) {
    fmt::print("Movie {} not found", name);
    return;
  }

  // Maybe a confirmation that the process worked.
  database->delete_element(name, 'm');
}

void Controller::delete_tvshow()
{
  auto database = get_database();
  fmt::print("Enter the tv show name. If name has spaces add _ (underscore)\n: ");
  std::string name;
  std::cin >> name;

  const bool found = database->search(name, 't');
  if (!found) {
    fmt::print("Tv Show {} not found", name);
    return;
  }

  // Maybe a confirmation that the process worked.
  database->delete_element(name, 't');
}
}  // namespace Pholos
