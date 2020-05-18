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

namespace internal {

bool movie_or_tvshow(char &user_choose) {
  fmt::print("Movie [m] or Tv Show [t]? : ");
  bool user_choice = false;

  do {
    std::cin >> user_choose;

    if (std::tolower(user_choose) == 'm') {
      user_choice = true;
    } else if (std::tolower(user_choose) == 't') {
      user_choice = true;
    } else if (std::tolower(user_choose) == 'c') {
      user_choice = true;
      break;
    } else {
      fmt::print("Wrong option! Enter [m] or [t].\n");
      fmt::print("Enter [c] to cancel. : ");
    }
  } while (!user_choice);
  std::cin.clear();

  return user_choice;
}

}  // namespace internal

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
  } else if (command == "ABOUT") {
    x = 6;
  } else if (command == "LIST") {
    x = 7;
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

        EDIT    edit
                Edit an object.

        DELETE  delete
                Delete an object.

        SEARCH  search
                Search for an object.

        LIST    list
                List all
                List all movies or tv show.
                List by filters (e.g. list completed movies or/and tv show)

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
  char user_choose;
  bool user_chose = internal::movie_or_tvshow(user_choose);
  if (user_chose && std::tolower(user_choose) == 'm') {
    this->add_movie();
  } else if (user_chose && std::tolower(user_choose) == 't') {
    this->add_tvshow();
  } else if (user_chose && std::tolower(user_choose) == 'c') {
    return;
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
      "Enter the stat.\n Watching (1)\n Plan to Watch (2)\n Completed (3)\n Dropped (4)\n-> ");
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
  database->save(movie);
  this->load_content();
}

void Controller::add_tvshow() {
  int stat{-1};
  double rating{0.0};
  int episode{0};
  int last_episode{0};

  fmt::print(
    "\n***\nNote: Currently, Pholos doesn't support season. That means if you "
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
    fmt::print(
      "Enter the stat.\n Watching (1)\n Plan to Watch (2)\n Completed (3)\n Dropped (4)\n-> ");
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
  database->save(tvshow);
  this->load_content();
}

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
  fmt::print("\n");
  if (this->movies_cache_.empty()) {
    fmt::print("\n***\nYour movie list is empty!\n");
    return;
  }

  // Get the length of the biggest movie's name.
  // id width | word width | rating width | stat width |
  // 0          1            2            3
  // Id | Name | Rating | Stat
  // 4    5      6        7
  std::size_t biggest_word = 0;
  std::for_each(this->movies_cache_.begin(), this->movies_cache_.end(), [&](const auto &obj) {
    std::size_t movie_name_length = obj.second.name().size();
    biggest_word = movie_name_length > biggest_word ? movie_name_length : biggest_word;
  });

  // TODO: Turn this into a routine
  // TOP
  fmt::print(" -{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}- \n", Width::ID, biggest_word,
             Width::Rating, Width::Stat, "");
  fmt::print("| {4:<{0}} | {5:<{1}} | {6:<{2}} | {7:<{3}} |\n", Width::ID, biggest_word,
             Width::Rating, Width::Stat, "Movie ID", "Name", "Rating", "Stat");

  // MID
  fmt::print(" -{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}- \n", Width::ID, biggest_word,
             Width::Rating, Width::Stat, "");

  std::for_each(this->movies_cache_.begin(), this->movies_cache_.end(), [=](const auto &obj) {
    fmt::print("| {4:<{0}} | {5:<{1}} | {6:<{2}} | {7:<{3}} |\n", Width::ID, biggest_word,
               Width::Rating, Width::Stat, obj.first, obj.second.name(), obj.second.rating(),
               obj.second.stat_as_string());
  });

  // BOTTOM
  fmt::print(" -{4:-^{0}}---{4:-^{1}}---{4:-^{2}}---{4:-^{3}}- \n", Width::ID, biggest_word,
             Width::Rating, Width::Stat, "");
}

void Controller::list_all_tvshows() {
  fmt::print("\n");
  if (this->tvshow_cache_.empty()) {
    fmt::print("Your tv show list is empty!\n");
    return;
  }

  // id width | word width | rating width | stat width | episode width | total episode
  // 0          1            2              3            4               5
  // Id | Name | Rating | Stat | Episode | Total Episodes
  // 6    7      8        9      10        11

  std::size_t biggest_word = 0;
  std::for_each(this->tvshow_cache_.begin(), this->tvshow_cache_.end(), [&](const auto &obj) {
    std::size_t tv_name_length = obj.second.name().size();
    biggest_word               = tv_name_length > biggest_word ? tv_name_length : biggest_word;
  });

  // TODO: Turn this into a routine
  // TOP
  fmt::print(" -{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}- \n",
             Width::ID + 2, biggest_word, Width::Rating, Width::Stat, Width::Episode,
             Width::Total_Episode, "");
  fmt::print("| {6:<{0}} | {7:<{1}} | {8:<{2}} | {9:<{3}} | {10:<{4}} | {11:<{5}} |\n",
             Width::ID + 2, biggest_word, Width::Rating, Width::Stat, Width::Episode,
             Width::Total_Episode, "Tv Show ID", "Name", "Rating", "Stat", "Episode",
             "Total Episodes");

  // MID
  fmt::print(" -{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}- \n",
             Width::ID + 2, biggest_word, Width::Rating, Width::Stat, Width::Episode,
             Width::Total_Episode, "");

  std::for_each(this->tvshow_cache_.begin(), this->tvshow_cache_.end(), [=](const auto &obj) {
    fmt::print("| {6:<{0}} | {7:<{1}} | {8:<{2}} | {9:<{3}} | {10:<{4}} | {11:<{5}} |\n",
               Width::ID + 2, biggest_word, Width::Rating, Width::Stat, Width::Episode,
               Width::Total_Episode, obj.first, obj.second.name(), obj.second.rating(),
               obj.second.stat_as_string(), obj.second.episode(), obj.second.last_episode());
  });

  // BOTTOM
  fmt::print(" -{6:-^{0}}---{6:-^{1}}---{6:-^{2}}---{6:-^{3}}---{6:-^{4}}---{6:-^{5}}- \n",
             Width::ID + 2, biggest_word, Width::Rating, Width::Stat, Width::Episode,
             Width::Total_Episode, "");
}

bool Controller::id_exist(const int id, const char obj_type) {
  auto found = false;
  if (std::tolower(obj_type) == 'm') {
    if (auto search = this->movies_cache_.find(id); search != this->movies_cache_.end()) {
      found = true;
    }
  } else if (std::tolower(obj_type) == 't') {
    if (auto search = this->tvshow_cache_.find(id); search != this->tvshow_cache_.end()) {
      found = true;
    }
  }
  return found;
}

void Controller::edit() {
  // Which object we want to edit: movie or tv show.
  char user_choose;
  bool user_chose = internal::movie_or_tvshow(user_choose);

  if (user_chose && std::tolower(user_choose) != 'c') {
    this->edit_menu(user_choose);
  } else {
    return;
  }
}

void Controller::edit_menu(char movie_or_tv) {
  int edit_option = 0;

  fmt::print(
    "\n***\nNote: You must know the object id in other to edit.\nUse list all to get the id.\n\n");
  // Check for object's id.
  int id     = internal::get_user_input<int>("Please enter the id.\n-> ");
  bool exist = this->id_exist(id, movie_or_tv);

  if (!exist) {
    fmt::print("The id doesn't exist.\n");
    return;
  }

  // TODO: handle wrong usage: edit_option > 5 and < 1;
  if (std::tolower(movie_or_tv) == 'm') {
    fmt::print("Edit options:\n Change name (1)\n Change stat (2)\n Change rating (3)\n\n-> ");
    std::cin >> edit_option;
  } else if (std::tolower(movie_or_tv) == 't') {
    fmt::print(
      "Edit options:\n Change name (1)\n Change stat (2)\n Change rating (3)\n Change episode "
      "(4)\n "
      "Change total episode (5)\n\n-> ");
    std::cin >> edit_option;
  }

  // TODO: handle wrong user input
  // We update the objects in database using the ID.
  auto *database = get_database();
  switch (edit_option) {
    case 1:
      fmt::print("Enter the new name, please.\n-> ");
      {
        std::string name;
        std::cin.get();
        std::getline(std::cin, name);
        database->update_name(id, name, movie_or_tv);
      }
      break;
    case 2: {
      const int stat = internal::get_user_input<int>(
        "Enter the new stat:\n Watching (1)\n Plan to Watch (2)\n Completed (3)\n Dropped "
        "(4)\n-> ");
      database->update_stat(id, stat, movie_or_tv);
    } break;
    case 3: {
      const double rating = internal::get_user_input<double>("Enter the new rating.\n-> ");
      database->update_rating(id, rating, movie_or_tv);
    } break;
    case 4: {
      // We ask user the number of episodes to increment. Default is by 1.
      const bool update_more_than_one =
        internal::get_user_input<bool>("Do you want to update more than 1? (y/n)\n-> ");
      if (update_more_than_one) {
        const int distance = internal::get_user_input<int>("Enter the amount to increment.\n-> ");
        database->update_episode(id, movie_or_tv, distance);
      } else {
        database->update_episode(id, movie_or_tv);
      }
    } break;
    case 5: {
      const int total_episode = internal::get_user_input<int>("Enter the new total episode.\n-> ");
      database->update_total_episode(id, total_episode, movie_or_tv);
    } break;
    default:
      fmt::print("Unhandled case!!!\n");
      break;
  }

  // LOL: We have to update the cache.
  this->load_content();
}
}  // namespace Pholos
